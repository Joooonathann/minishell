#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int calculate_size(t_tokens *command)
{
    int count = 0;

    while (command)
    {
        if (command->type == TYPE_PIPE)
            count++;
        command = command->next;
    }
    return (count + 2);  // Nombre de commandes = nombre de pipes + 1, +1 pour le NULL final
}

void trim_whitespace(char **str)
{
    char *end;

    // Trim leading space
    while(isspace((unsigned char)**str)) (*str)++;

    if(*str == 0) return;

    // Trim trailing space
    end = *str + strlen(*str) - 1;
    while(end > *str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end+1) = 0;
}

void handle_pipe(char **commands, t_vars **env, char **cpy_path)
{
    int pipefd[2];
    pid_t pid;
    int i = 0;
    int prev_fd = -1;  // Fichier descriptif précédent pour la redirection

    while (commands[i])
    {
        int redirect_fd = -1;  // Descripteur pour redirection
        char *output_file = NULL;
        char *cmd = commands[i];
        int j = 0;

        // Chercher la dernière redirection dans la commande
        while (cmd[j])
        {
            if (cmd[j] == '>')
            {
                cmd[j] = '\0';  // Terminer la chaîne de commande à la redirection
                output_file = &cmd[j + 1];  // Obtenir le nom du fichier de sortie
            }
            j++;
        }

        if (output_file) {
            trim_whitespace(&output_file);  // Supprimer les espaces autour du nom du fichier
        }

        if (pipe(pipefd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) // Processus enfant
        {
            if (prev_fd != -1) // Rediriger l'entrée si commande précédente
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            if (output_file) // Si redirection vers un fichier
            {
                redirect_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (redirect_fd < 0)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                dup2(redirect_fd, STDOUT_FILENO);
                close(redirect_fd);
            }
            else if (commands[i + 1]) // Si pas de redirection, rediriger vers le pipe
            {
                dup2(pipefd[1], STDOUT_FILENO);
            }

            close(pipefd[0]); // Fermer les descripteurs inutilisés
            close(pipefd[1]);

            handler_command(parser(cmd, env), env, cpy_path);
            exit(EXIT_SUCCESS);
        }
        else // Processus parent
        {
            close(pipefd[1]); // Fermer le côté écriture du pipe
            if (prev_fd != -1)
                close(prev_fd); // Fermer l'entrée de la commande précédente
            prev_fd = pipefd[0]; // Garder l'entrée pour la prochaine commande
        }
        i++;
    }

    // Attendre tous les processus enfants
    for (int j = 0; j < i; j++)
        wait(NULL);

    if (prev_fd != -1)
        close(prev_fd); // Fermer le dernier fd après toutes les commandes
}

int handler_special(t_tokens *command, t_vars **env, char **cpy_path)
{
    char **test;
    int i;
    char *current_command;

    test = malloc(sizeof(char *) * calculate_size(command));
    if (!test)
        return (1);
    i = 0;
    current_command = NULL;

    while (command)
    {
        if (command->type == TYPE_PIPE)
        {
            if (current_command)
                test[i++] = current_command;
            current_command = NULL;
        }
        else
        {
            char *temp = current_command;
            if (!temp)
                current_command = ft_strdup(command->value);
            else
            {
                char *new_command = ft_strjoin(temp, " ");
                char *joined_command = ft_strjoin(new_command, command->value);
                free(new_command);
                free(temp);
                current_command = joined_command;
            }
        }
        command = command->next;
    }

    if (current_command)
        test[i++] = current_command;
    test[i] = NULL;

    handle_pipe(test, env, cpy_path);

    // Libération de la mémoire
    i = 0;
    while (test[i])
        free(test[i++]);
    free(test);

    return (0);
}

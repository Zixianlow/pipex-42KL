/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzi-xian <lzi-xian@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:42:39 by lzi-xian          #+#    #+#             */
/*   Updated: 2023/02/07 13:56:39 by lzi-xian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_get_command_path(char	**paths, char *cmd)
{
	int		i;
	char	*temp;
	char	*command;
	char	**sptcmd;

	i = 0;
	if (access(cmd, 0) == 0)
		return (cmd);
	sptcmd = ft_split(cmd, '/');
	while (sptcmd[i])
		i++;
	i--;
	cmd = sptcmd[i];
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(temp, cmd);
		free(temp);
		if (access(command, 0) == 0)
			return (command);
		i++;
		free(command);
	}
	return (NULL);
}

void	ft_second_child(t_pipex	*pipex, char **av, char **env)
{
	char	**arr;
	int		i;

	i = 0;
	dup2(pipex->fd[0], 0);
	close(pipex->fd[1]);
	dup2(pipex->outfile, 1);
	arr = ft_split(av[3], ' ');
	pipex->cmd_path = ft_get_command_path(pipex->env_paths_arr, arr[0]);
	if (!pipex->cmd_path)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		perror("Command not found\n");
		exit(1);
	}
	execve(pipex->cmd_path, arr, env);
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}

void	ft_first_child(t_pipex	*pipex, char **av, char **env)
{
	char	**arr;
	int		i;

	i = 0;
	dup2(pipex->fd[1], 1);
	close(pipex->fd[0]);
	dup2(pipex->infile, 0);
	arr = ft_split(av[2], ' ');
	pipex->cmd_path = ft_get_command_path(pipex->env_paths_arr, arr[0]);
	if (!pipex->cmd_path)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		perror("Command not found\n");
		exit(1);
	}
	execve(pipex->cmd_path, arr, env);
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
}

void	ft_fork_and_child(t_pipex *pipex, char **av, char **env)
{
	pipex->id = fork();
	if (pipex->id == -1)
	{
		perror("Error!");
		exit(0);
	}
	if (pipex->id == 0)
		ft_first_child(pipex, av, env);
	pipex->id2 = fork();
	if (pipex->id2 == -1)
	{
		perror("Error!");
		exit(0);
	}
	if (pipex->id2 == 0)
		ft_second_child(pipex, av, env);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	waitpid(pipex->id, NULL, 0);
	waitpid(pipex->id2, NULL, 0);
}

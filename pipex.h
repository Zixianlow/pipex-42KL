/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzi-xian <lzi-xian@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:06:42 by lzi-xian          #+#    #+#             */
/*   Updated: 2023/02/07 13:59:27 by lzi-xian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./libft/libft.h"

typedef struct s_pipex
{
	int		fd[2];
	int		infile;
	int		outfile;
	pid_t	id;
	pid_t	id2;
	char	*env_paths_str;
	char	**env_paths_arr;
	char	*cmd_path;
	char	**env;
	char	**av;
}	t_pipex;

char	*ft_get_command_path(char	**paths, char *cmd);
void	ft_second_child(t_pipex	*pipex, char **av, char **env);
void	ft_first_child(t_pipex	*pipex, char **av, char **env);
void	ft_fork_and_child(t_pipex *pipex, char **av, char **env);

#endif
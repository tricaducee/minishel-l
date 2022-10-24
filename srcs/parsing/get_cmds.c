/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrolle <hrolle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 00:31:19 by hermesrolle       #+#    #+#             */
/*   Updated: 2022/10/24 20:12:54 by hrolle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	print_error(char *s)
{
	if (!s)
		printf("Error\n");
	else
		printf("Error on %s\n", s);
}

static int	ft_strcmp_int(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 || *s2)
		return (0);
	return (1);
}

static int	ft_strslen(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*split_cmd(char *cmdline, unsigned int *i, char c)
{
	unsigned int	j;

	j = 0;
	while (cmdline[*i + j] && (cmdline[*i + j] == c))
		++j;
	*i += j;
	return (ft_substr(cmdline, *i - j, j));
}

static char	**ft_strsjoin(char *s, char **ss)
{
	char			**ret;
	unsigned int	i;

	ret	= malloc((ft_strslen(ss) + 2) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (ss && ss[i])
	{
		ret[i] = ss[i];
		++i;
	}
	ret[i] = s;
	ret[++i] = 0;
	return (ret);
}

char	*add_var(char *cmdline, char *str, unsigned int *i, t_list *env)
{
	char			*ret;
	unsigned int	j;
	char			*tmp;
	char			*new;

	j = 0;
	++*i;
	ret = NULL;
	while (cmdline[*i + j] && cmdline[*i + j] != '$' && cmdline[*i + j]
				!= ' ' && cmdline[*i + j] != '<' && cmdline[*i + j]
				!= '>' && cmdline[*i + j] != '|' && cmdline[*i + j]
				!= '&' && cmdline[*i + j] != '\'' && cmdline[*i + j] != '"')
		j++;
	if (j)
	{
		//new = ft_get_env(t_list *env, ft_substr(cmdline, *i, j)); //---------------------------- Chercher variable
		(void)env;
		new = ft_strdup("VARIABLE");
	}
	else
		new = ft_strdup("$");
	tmp = str;
	ret = ft_strjoin(str, new);
	free(new);
	if (tmp)
		free(tmp);
	if (!ret)
		return (NULL);
	*i += j;
	return (ret);
}

char	*add_quote(char *cmdline, char *str, unsigned int *i)
{
	char			*ret;
	unsigned int	j;
	char			*tmp;
	char			*new;

	j = 0;
	++*i;
	ret = NULL;
	while (cmdline[*i + j] && cmdline[*i + j] != '\'')
		j++;
	tmp = str;
	new = ft_substr(cmdline, *i, j);
	ret = ft_strjoin(str, new);
	free(new);
	if (!ret)
		return (NULL);
	if (tmp)
		free(tmp);
	*i += j + 1;
	return (ret);
}

char	*add_dquote(char *cmdline, char *str, unsigned int *i, t_list *env)
{
	char			*ret;
	unsigned int	j;
	char			*tmp;
	char			*new;

	++*i;
	ret = str;
	while (cmdline[*i] && cmdline[*i] != '"')
	{
		j = 0;
		while (cmdline[*i + j] && cmdline[*i + j] != '"' && cmdline[*i + j] != '$')
			j++;
		tmp = ret;
		new = ft_substr(cmdline, *i, j);
		ret = ft_strjoin(tmp, new);
		free(new);
		if (!ret)
			return (NULL);
		if (tmp)
			free(tmp);
		*i += j;
		if (cmdline[*i] && cmdline[*i] == '$')
			ret = add_var(cmdline, ret, i, env);
	}
	++*i;
	return (ret);
}

char	*split_cmd_sp(char *cmdline, unsigned int *i, t_list *env)
{
	unsigned int	j;
	char			*ret;
	char			*tmp;
	char			*new;

	ret = NULL;
	while (cmdline[*i] && cmdline[*i] != ' ' && cmdline[*i] != '<' && cmdline[*i]
				!= '>' && cmdline[*i] != '|' && cmdline[*i] != '&')
	{
		j = 0;
		while (cmdline[*i + j] && cmdline[*i + j] != '$' && cmdline[*i + j]
				!= ' ' && cmdline[*i + j] != '<' && cmdline[*i + j]
				!= '>' && cmdline[*i + j] != '|' && cmdline[*i + j]
				!= '&' && cmdline[*i + j] != '\'' && cmdline[*i + j] != '"')
			++j;
		if (j)
		{
			tmp = ret;
			new = ft_substr(cmdline, *i, j);
			ret = ft_strjoin(tmp, new);
			free(new);
			if (tmp)
				free(tmp);
			tmp = NULL;
		}
		*i += j;
		if (cmdline[*i] && cmdline[*i] == '$')
			ret = add_var(cmdline, ret, i, env);
		if (cmdline[*i] && cmdline[*i] == '\'')
			ret = add_quote(cmdline, ret, i);
		if (cmdline[*i] && cmdline[*i] == '"')
			ret = add_dquote(cmdline, ret, i, env);
	}
	return (ret);
}


void	print_tab(char **s)
{
	while (s && *s)
		printf("%s\n", *(s++));
}

void	free_tab(char **s)
{
	unsigned int	i;

	i = 0;
	while (s && s[i])
		free(s[i++]);
	if (s)
		free(s);
}

t_cmdli	*create_cmdli(void)
{
	t_cmdli	*ret;

	ret = malloc(1 * sizeof(t_cmdli));
	if (!ret)
		return (NULL);//------------------------------------------malloc return
	ret->cmd = NULL;
	ret->cmd_args = NULL;
	ret->pipe_in = NULL;
	ret->pipe_out = NULL;
	ret->here_doc = NULL;
	ret->fd_in = -1;
	ret->fd_out = -1;
	ret->and_or = 0;
	ret->previous = NULL;
	ret->next = NULL;
	return (ret);
}

void	add_pipe(t_cmdli **cmds_list, t_type *type)
{
	*type = PIPE;
	(*cmds_list)->next = create_cmdli();
	(*cmds_list)->next->previous = (*cmds_list);
	if (!(*cmds_list)->pipe_out)
		(*cmds_list)->pipe_out = malloc(2 * sizeof(int));
	(*cmds_list)->next->pipe_in = (*cmds_list)->pipe_out;
	*cmds_list = (*cmds_list)->next;
	if (pipe((*cmds_list)->pipe_in) == -1)
		return (print_error("pipe"));
}

void	add_andor(t_cmdli **cmds_list, t_type *type, int and_or)
{
	*type = ANDOR;
	(*cmds_list)->next = create_cmdli();
	(*cmds_list)->next->previous = (*cmds_list);
	*cmds_list = (*cmds_list)->next;
	(*cmds_list)->and_or = and_or;
}

void	add_arg(t_cmdli **cmds_list, char *arg, t_type *type)
{
	char	**tmp;

	*type = ARG;
	tmp = (*cmds_list)->cmd_args;
	(*cmds_list)->cmd_args = ft_strsjoin(arg, tmp);
	if (tmp)
		free(tmp);
}

void	add_cmd(t_cmdli **cmds_list, char *cmd, t_type *type)
{
	*type = CMD;
	(*cmds_list)->cmd = cmd;
}

void	add_file(t_cmdli **cmds_list, char *file, t_type *type)//--------------------------------------------------------------------------------------------------------
{
	if (*type == RDI)
	{
		if ((*cmds_list)->fd_in != -1)
			close((*cmds_list)->fd_in);
		(*cmds_list)->fd_in = open(file, O_RDONLY);
		if ((*cmds_list)->fd_in == -1)
			return (print_error(file));
		free(file);
		//if (!(*cmds_list)->pipe_in)
		//	(*cmds_list)->pipe_in = malloc(2 * sizeof(int));
		//if (!(*cmds_list)->pipe_in)
		//	return (print_error(file));
		//pipe((*cmds_list)->pipe_in);
	}
	else if (*type == RDO)
	{
		if ((*cmds_list)->fd_out != -1)
			close((*cmds_list)->fd_out);
		(*cmds_list)->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if ((*cmds_list)->fd_out == -1)
			return (print_error(file));
		free(file);
	}
	else if (*type == RDOA)
	{
		if ((*cmds_list)->fd_out != -1)
			close((*cmds_list)->fd_out);
		(*cmds_list)->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((*cmds_list)->fd_out == -1)
			return (print_error(file));
		free(file);
	}
	else
	{
		if (!(*cmds_list)->pipe_in)
	}
	*type = RFILE;
}

void	type_and_set(char *s, t_cmdli **cmds_list, t_type *type, int interpret) // doit retourner valeur si continue ou pas
{
	int	rd;

	//printf("\ntype_and_set in\n");
	if (*type == RDI || *type == RDO || *type == RDIH || *type == RDOA)
		rd = 1;
	else
		rd = 0;
	if (!*cmds_list)
	{
		*cmds_list = create_cmdli();
		//print_cmdli(*cmds_list);
	}
	if (!*cmds_list)
		return ;
	if (interpret) // for <<<< <<< >>>> ||| etc... print s + 2
	{
		if (ft_strcmp_int(s, "<") && !rd)
			*type = RDI;
		else if (ft_strcmp_int(s, "<<") && !rd)
			*type = RDIH;
		else if (ft_strcmp_int(s, ">") && !rd)
			*type = RDO;
		else if (ft_strcmp_int(s, ">>") && !rd)
			*type = RDOA;
		else if (ft_strcmp_int(s, "|") && ((*type == CMD || *type == ARG) || ((*cmds_list)->cmd  && *type == RFILE)))
			add_pipe(cmds_list, type);
		else if (ft_strcmp_int(s, "||") && ((*type == CMD || *type == ARG) || ((*cmds_list)->cmd && *type == RFILE)))
			add_andor(cmds_list, type, 2);
		else if (ft_strcmp_int(s, "&&") && ((*type == CMD || *type == ARG) || ((*cmds_list)->cmd && *type == RFILE)))
			add_andor(cmds_list, type, 1);
		else
		{
			//printf("\ntype_and_set out\n");
			return (print_error(s));
		}
	}
	else
	{
		if (*type == CMD || *type == ARG)
			add_arg(cmds_list, s, type);
		else if (!rd)
			add_cmd(cmds_list, s, type);
		else
			add_file(cmds_list, s, type);
	}
	//printf("\ntype_and_set out\n");
}

t_cmdli	*cmdli_first(t_cmdli *cmds_list)
{
	//printf("\ncmdli_first in\n");
	if (!cmds_list)
		return (NULL);
	while (cmds_list->previous)
		cmds_list = cmds_list->previous;
	//printf("\ncmdli_first out\n");
	return (cmds_list);
}

t_cmdli	*get_cmds(t_list *env, char *cmdline)
{
	//printf("\nget_cmds in\n");
	unsigned int	i;
	t_cmdli			*cmds_list;
	t_type				type;

	if (!cmdline)
		return (NULL);
	i = 0;
	type = 0;
	cmds_list = NULL;
	while (cmdline[i])
	{
		while (cmdline[i] == ' ') //all white space
			++i;
		if (cmdline[i] == '<')
			type_and_set(split_cmd(cmdline, &i, '<'), &cmds_list, &type, 1);
		else if (cmdline[i] == '>')
			type_and_set(split_cmd(cmdline, &i, '>'), &cmds_list, &type, 1);
		else if (cmdline[i] == '|')
			type_and_set(split_cmd(cmdline, &i, '|'), &cmds_list, &type, 1);
		else if (cmdline[i] == '&')
			type_and_set(split_cmd(cmdline, &i, '&'), &cmds_list, &type, 1);
		else
			type_and_set(split_cmd_sp(cmdline, &i, env), &cmds_list, &type, 0);
		if (!cmds_list)
			return (NULL);
	}
	//printf("\nget_cmds out\n");
	return (cmdli_first(cmds_list));
}


// t_cmdli	*get_cmds(char *cmdline)
// {
// 	unsigned int	i;
// 	t_cmdli			*cmds_list;
// 	char			**cmds_tab;
// 	char			**tmp;

// 	if (!cmdline)
// 		return (NULL);
// 	i = 0;
// 	cmds_list = NULL;
// 	cmds_tab = NULL;
// 	while (cmdline[i])
// 	{
// 		while (cmdline[i] == ' ') //all white space
// 			++i;
// 		tmp = cmds_tab;
// 		if (cmdline[i] == '<')
// 			type_and_set(split_cmd(cmdline, &i, '<'), cmds_tab);
// 		else if (cmdline[i] == '>')
// 			type_and_set(split_cmd(cmdline, &i, '>'), cmds_tab);
// 		else if (cmdline[i] == '|')
// 			type_and_set(split_cmd(cmdline, &i, '|'), cmds_tab);
// 		else if (cmdline[i] == '&')
// 			type_and_set(split_cmd(cmdline, &i, '&'), cmds_tab);
// 		else
// 			type_and_set(split_cmd_sp(cmdline, &i), cmds_tab);
// 		if (tmp)
// 			free(tmp);
// 		tmp = NULL;
// 	}
// 	print_tab(cmds_tab);
// 	free_tab(cmds_tab);
// 	return (cmds_list);
// }

// int	main(int ac, char **av)
// {
// 	if (ac < 2)
// 		return (1);
// 	print_cmdli(get_cmds(av[1]));
// 	return (0);
// }

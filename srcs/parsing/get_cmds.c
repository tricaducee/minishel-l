/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 00:31:19 by hermesrolle       #+#    #+#             */
/*   Updated: 2022/10/24 04:34:27 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_cmds.h"
#include <stdio.h>//----------------------------------------------

void	print_error(char *s)
{
	if (!s)
		printf("Error\n");
	else
		printf("Error on %s\n", s);
}

static size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static int	ft_strcmp(char *s1, char *s2)
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

static char	*ft_strdup(char *s)
{
	char			*ret;
	unsigned int	i;

	if (!s)
		return (NULL);
	ret	= malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		++i;
	}
	ret[i] = 0;
	return (ret);
}

static char	*ft_substr(char *s, unsigned int start, unsigned int len)
{
	char			*ret;
	unsigned int	i;
	unsigned int	f_len;

	if (!s)
		return (0);
	f_len = ft_strlen(s);
	if (start >= f_len)
		return (ft_strdup(""));
	if (len > f_len - start)
		len = f_len - start;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (0);
	i = 0;
	while (s[start + i] && i < len)
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*ret;

	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	ret = str;
	if (!str)
		return (0);
	while (s1 && *s1)
		*(str++) = *(s1++);
	while (s2 && *s2)
		*(str++) = *(s2++);
	*str = 0;
	return (ret);
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

char	*add_var(char *cmdline, char *str, unsigned int *i)
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
		new = ft_strdup("VARIABLE"); //---------------------------- Chercher variable
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

char	*add_dquote(char *cmdline, char *str, unsigned int *i)
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
			ret = add_var(cmdline, ret, i);
	}
	++*i;
	return (ret);
}

char	*split_cmd_sp(char *cmdline, unsigned int *i)
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
			ret = add_var(cmdline, ret, i);
		if (cmdline[*i] && cmdline[*i] == '\'')
			ret = add_quote(cmdline, ret, i);
		if (cmdline[*i] && cmdline[*i] == '"')
			ret = add_dquote(cmdline, ret, i);
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
	ret->cmd_path = NULL;
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

// EMPTY	0
// CMD,	1
// ARG,	1
// PIPE,	0
// RFILE,	Si cmdpath != NULL
// RDI,	0
// RDO,	0
// RDIH,	0
// RDOA,	0
// ANDOR	0

void	add_pipe(t_cmdli **cmds_list, t_type *type)
{
	*type = PIPE;
	(*cmds_list)->next = create_cmdli();
	(*cmds_list)->next->previous = (*cmds_list);
	(*cmds_list)->pipe_out = malloc(2 * sizeof(int));
	(*cmds_list)->next->pipe_in = (*cmds_list)->pipe_out;
	*cmds_list = (*cmds_list)->next;
	if (pipe((*cmds_list)->pipe_in) == -1)
		return (print_error("pipe"));
}

void	type_and_set(char *s, t_cmdli **cmds_list, t_type *type, int interpret)
{
	int	rd;

	if (*type == RDI || *type == RDO || *type == RDIH || *type == RDOA)
		rd = 1;
	else
		rd = 0;
	if (!*cmds_list)
		*cmds_list = create_cmdli();
	if (!*cmds_list)
		return ;
	if (interpret) // for <<<< <<< >>>> ||| etc... print s + 2
	{
		if (ft_strcmp(s, "<") && !rd)
			*type = RDI;
		else if (ft_strcmp(s, "<<") && !rd)
			*type = RDIH;
		else if (ft_strcmp(s, ">") && !rd)
			*type = RDO;
		else if (ft_strcmp(s, ">>") && !rd)
			*type = RDOA;
		else if (ft_strcmp(s, "|") && ((*type == CMD || *type == ARG) || ((*cmds_list)->cmd_path) && *type == RFILE))
			add_pipe(cmds_list, type);
		else if (ft_strcmp(s, "||") && ((*type == CMD || *type == ARG) || ((*cmds_list)->cmd_path) && *type == RFILE))
			*type = ANDOR;
		else if (ft_strcmp(s, "&&") && ((*type == CMD || *type == ARG) || ((*cmds_list)->cmd_path) && *type == RFILE))
			*type = ANDOR;
	}
}

t_cmdli	*cmdli_first(t_cmdli *cmds_list)
{
	while (cmds_list->previous)
		cmds_list = cmds_list->previous;
	return (cmds_list);
}

t_cmdli	*get_cmds(char *cmdline)
{
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
			type_and_set(split_cmd_sp(cmdline, &i), &cmds_list, &type, 0);
		if (!cmds_list)
			return (NULL);
	}
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
// 	get_cmds(av[1]);
// 	return (0);
// }
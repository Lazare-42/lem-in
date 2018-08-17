#include "../includes/lemin.h"
#include "../libft/includes/libft.h"

static t_node	*get_tubes(t_info info, char *buf)
{
	int		ret;

	info = swap_end_room(info);
	info = create_tubes(info);
	ret = 1;
	while (ret > 0)
	{
		if (buf[0] == '#')
			comment_mannagement(buf);
		else
			info = tube_assign(buf, info);
		ft_memdel((void**)&buf);
		ret = get_next_line(0, &buf, '\n');
	}
	return (info.nodelist);
}

static t_info	get_rooms(t_info info, char *buf)
{
	int		ret;
	int		node_number;

	ret = 1;
	node_number = 0;
	buf = NULL;
	while (ret > 0)
	{
		ft_memdel((void**)&buf);
		ret = get_next_line(0, &buf, '\n');
		if (ret > 0 && ft_strchr(buf, '-'))
		{
			info.nodelist = (get_tubes(info, buf));
			return (info);
		}
		else if (ret > 0 && buf[0] == '#')
		{
			if (ft_memcmp(buf, "##end", 5))
				comment_mannagement(buf);
			else
				info.end_room = 1;
			continue ;
		}
		info  = store_node_handler(info, node_create(buf, node_number++));
		info.end_room = 0;
	}
	lemin_error("no tubes after room declaration or GNL return was < 1");
	return (info);
}

t_info			parse_map(t_info info)
{
	char	*buf;
	int		ret;
	int		started;

	ret = 1;
	buf = NULL;
	started = 0;
	while (ret > 0)
	{
		ret = get_next_line(0, &buf, '\n');
		if (ret == -1)
			lemin_error("get_next_line returned -1 in parse_map");
		if (buf && ft_strstr(buf, "##start"))
		{
			info = get_rooms(info, buf);
			started = 1;
			ret = 0;
		}
		ft_memdel((void**)&buf);
	}
	if (!(started))
		lemin_error("no rooms to start");
	return (info);
}

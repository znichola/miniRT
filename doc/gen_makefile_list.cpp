/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_makefile_list.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:57:36 by znichola          #+#    #+#             */
/*   Updated: 2023/05/29 11:13:39 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <dirent.h>

using std::cout;

class File
{
	public:
	std::string		name;

	std::vector<File> bag;
};

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		cout << "example usage: ./a.out srcs/";
		return 1;
	}

	DIR				*dir = opendir(av[1]);
	struct dirent	*dir_entry = readdir(dir);
	while (dir_entry)
	{
		;
	}
	return 0;
}

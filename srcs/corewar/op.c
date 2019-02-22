/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-spie <sde-spie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 17:15:36 by sde-spie          #+#    #+#             */
/*   Updated: 2019/02/22 13:25:57 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


/*
 * partout ou on a % MEM_SIZE peut etre faire & 0xFFF car MEM_SIZE 4096
 * ca marcherait avec positif et negatif, exemple, en -1 :
 * en int c'est 11111111 111111111 111111111 11111111 si je fais -1 & 0xFFF
 * j'ai 00001111 11111111 qui est 4095, magie.
 * D'ailleurs, c'est moins couteux qu'un modulo.
 */

void			op_null(t_vm *vm, t_process *process)
{
	/*
	 * on peut mettre + process->instruction.adv au lieu +1 mais dans tous les
	 * cas vaut 1
	 */

	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + 1) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

/*
 * vm->arena.winner veut l'index du champ winner pas son number.
 * le process se dit en vie, meme si le num du joueur est un joueur inexistant
 */

void			op_live(t_vm *vm, t_process *process)
{
	int		i;

	(process->lives_since_check)++;
	i = 0;
	while (i < vm->nbr_champ)
	{
		if (vm->champs[i].number == process->instruction.value[0])
		{
			(vm->champs[i].lives)++;
			(vm->champs[i].lives_since_last_check)++;
			vm->arena.winner = i;
			(vm->arena.lives_since_last_check)++;
			// if (vm->visu == 0)
			// 	ft_printf("un processus dit que le joueur %d %s est en vie\n",\
			// 		process->instruction.value[0],\
			// 		vm->champs[i].code.header.prog_name);
			break ;
		}
		i++;
	}
	//pareil, on peut mettre process->instruction.adv au lieu de 5
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + 5) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

/*
 * si on recoit une valeur directe, on la load directement, sans changement.
 * si on recoit une valeur indirecte, on va aller copier REG_SIZE (4) octets
 * de la memoire a l'endroit de la (pc + value[0] % IDX_MOD) % MEM_SIZE dans
 * le registre
 */

void			op_ld(t_vm *vm, t_process *process)
{
	int			*val;
	t_arg_type	*type;

	type = process->instruction.types;
	if (type[0] != -1)
	{
		val = process->instruction.value;
		if (type[0] == T_IND)
		{
			val[0] = big_end_toi(vm->arena.arena,
					(process->pc + val[0] % IDX_MOD) & 0xFFF, REG_SIZE);
		}
		process->carry = (val[0] == 0);
		process->registre[val[1]] = val[0];
	}
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

/* lit_end_tovm et big_end_toi (qui est pour l'instant dans op_get_params)
 * a mettre dans un fichier helper a cote peut etre et plus en static
 */

static void		lit_end_tovm(t_vm *vm, int pc, int value, int champ_index)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		vm->arena.arena[(pc + i) % MEM_SIZE] = (value >> (24 - i * 8)) & 0xFF;
		vm->arena.arena_owner[(pc + i) % MEM_SIZE] = champ_index;
		i++;
	}
}

void			op_st(t_vm *vm, t_process *process)
{
	int			*val;
	t_arg_type	*type;

	type = process->instruction.types;
	if (type[0] != -1)
	{
		val = process->instruction.value;
		//printf("val[1] dans st : %d\n", val[1]);
		if (type[1] == T_REG)
			process->registre[val[1]] = process->registre[val[0]];
		else
			lit_end_tovm(vm, (process->pc + val[1] % IDX_MOD) & 0xFFF,
				process->registre[val[0]], process->index_champ);
	}
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

/*
 * il y a un octet d'encodage, useless, je sais pas pourquoi, mais ainsi va la
 * vie (pour add et sub. Ah et aussi pour aff, mais ils ont fait remarquer le
 * non sens d'en avoir un dans le sujet alors ca me choque moins.
 */

void			op_add(t_vm *vm, t_process *process)
{
	int			*val;
	t_arg_type	*type;
	int			sum;

	type = process->instruction.types;
	if (type[0] != -1)
	{
		val = process->instruction.value;
		sum = process->registre[val[0]] + process->registre[val[1]];
		process->registre[val[2]] = sum;
		process->carry = (sum == 0);
	}
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

void			op_sub(t_vm *vm, t_process *process)
{
	int			*val;
	t_arg_type	*type;
	int			sub;

	type = process->instruction.types;
	if (type[0] != -1)
	{
		val = process->instruction.value;
		sub = process->registre[val[0]] - process->registre[val[1]];
		process->registre[val[2]] = sub;
		process->carry = (sub == 0);
	}
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

void			op_and(t_vm *vm, t_process *process)
{
	int			*val;
	t_arg_type	*type;
	int			and;
	int			i;

	type = process->instruction.types;
	if (type[0] != -1)
	{
		val = process->instruction.value;
		i = 0;
		while (i < 2)
		{
			if (type[i] == T_REG)
				val[i] = process->registre[val[i]];
			else if (type[i] == T_IND)
				val[i] = big_end_toi(vm->arena.arena,
						(process->pc + val[i]) & 0xFFF, REG_SIZE);
			i++;
		}
		and = val[0] & val[1];
		process->registre[val[2]] = and;
		process->carry = (and == 0);
	}
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

void			op_or(t_vm *vm, t_process *process)
{
	int			*val;
	t_arg_type	*type;
	int			or;
	int			i;

	type = process->instruction.types;
	if (type[0] != -1)
	{
		val = process->instruction.value;
		i = 0;
		while (i < 2)
		{
			if (type[i] == T_REG)
				val[i] = process->registre[val[i]];
			else if (type[i] == T_IND)
				val[i] = big_end_toi(vm->arena.arena,
						(process->pc + val[i]) & 0xFFF, 4);
			i++;
		}
		or = val[0] | val[1];
		process->registre[val[2]] = or;
		process->carry = (or == 0);
	}
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

void			op_xor(t_vm *vm, t_process *process)
{
	int			*val;
	t_arg_type	*type;
	int			xor;
	int			i;

	type = process->instruction.types;
	if (type[0] != -1)
	{
		val = process->instruction.value;
		i = 0;
		while (i < 2)
		{
			if (type[i] == T_REG)
				val[i] = process->registre[val[i]];
			else if (type[i] == T_IND)
				val[i] = big_end_toi(vm->arena.arena,
						(process->pc + val[i]) & 0xFFF, 4);
			i++;
		}
		xor = val[0] ^ val[1];
		process->registre[val[2]] = xor;
		process->carry = (xor == 0);
	}
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

void			op_zjmp(t_vm *vm, t_process *process)
{
	int		new_pc;

	if (process->carry == 1)
		new_pc = (process->pc + process->instruction.value[0] % IDX_MOD) & 0xFFF;
	else
		new_pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = new_pc;
	vm->arena.arena_owner[process->pc] *= -1;
}

void			op_ldi(t_vm *vm, t_process *process)
{
	int			*val;
	t_arg_type	*type;
	int			i;
	int			sum;

	type = process->instruction.types;
	if (type[0] != -1)
	{
		val = process->instruction.value;
		i = 0;
		/*
		 * en fait faire une fonction de ca, je l'utilise tout le temps.
		 * mmmmh, non en fait. Il y a des differences.
		 */
		while (i < 2)
		{
			if (type[i] == T_REG)
				val[i] = process->registre[val[i]];
			else if (type[i] == T_IND)
				val[i] = big_end_toi(vm->arena.arena,
						(process->pc + val[i]) & 0xFFF, REG_SIZE);
			i++;
		}
		sum = val[0] + val[1];
		process->registre[val[2]] = big_end_toi(vm->arena.arena,
				(process->pc + sum % IDX_MOD) & 0xFFF, REG_SIZE);
	}
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

void			op_sti(t_vm *vm, t_process *process)
{
	int			*val;
	t_arg_type	*type;
	int			i;
	int			sum;

	type = process->instruction.types;
	if (type[0] != -1)
	{
		i = 0;
		val = process->instruction.value;
		while (i <= 2)
		{
			if (type[i] == T_REG)
				val[i] = process->registre[val[i]];
			/*
			 * pas de mod IDX_MOD quand on va chercher les parametres, alors
			 * verifier que j'ai bien fait ca aux autres aussi.
			 */
			else if (type[i] == T_IND)
				val[i] = big_end_toi(vm->arena.arena,
						(process->pc + val[i]) & 0xFFF, 4);
			i++;
		}
		//printf("valeur du val[0] dans sti : %d\n", val[0]);
		sum = val[1] + val[2];
		lit_end_tovm(vm, (process->pc + sum % IDX_MOD) & 0xFFF,
			val[0], process->index_champ);
	}
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

void			op_fork(t_vm *vm, t_process *process)
{
	int		n_proc;
	int		old_proc;

	n_proc = vm->arena.nbr_process;
	if (n_proc == vm->arena.s_proc)
	{
		old_proc = process->number;
		if (!(vm->arena.process = realloc(vm->arena.process,
				sizeof(t_process) * (vm->arena.s_proc * 2))))
			error_exit(vm, "allocation failed");
		vm->arena.s_proc *= 2;
		process = &(vm->arena.process[old_proc - 1]);
	}
	ft_memcpy((t_process *)&(vm->arena.process[n_proc]),
		(t_process*)process, sizeof(t_process));
	vm->arena.process[n_proc].pc = (process->pc +\
			(process->instruction.value[0] % IDX_MOD)) & 0xFFF;
	vm->arena.process[n_proc].number = n_proc;
	vm->arena.process[n_proc].instruction.op_code = 0;
	vm->arena.process[n_proc].lives_since_check = 0;
	(vm->arena.nbr_process)++;
	(vm->arena.nbr_process_alive)++;
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

/*
 * meme chose que ld sans % IDX_MOD
 */

void			op_lld(t_vm *vm, t_process *process)
{
	int			*val;
	t_arg_type	*type;

	type = process->instruction.types;
	if (type[0] != -1)
	{
		val = process->instruction.value;
		if (type[0] == T_IND)
			//remplacer 4 par REG_SIZE
			val[0] = big_end_toi(vm->arena.arena, (process->pc + val[0]) & 0xFFF, REG_SIZE);
		process->carry = (val[0] == 0);
		process->registre[val[1]] = val[0];
	}
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

/*
 * lui il modifie le carry, ldi pas.
 */
void			op_lldi(t_vm *vm, t_process *process)
{

	int			*val;
	t_arg_type	*type;
	int			i;
	int			sum;

	type = process->instruction.types;
	if (type[0] != -1)
	{
		val = process->instruction.value;
		i = 0;
		while (i < 2)
		{
			if (type[i] == T_REG)
				val[i] = process->registre[val[i]];
			else if (type[i] == T_IND)
				val[i] = big_end_toi(vm->arena.arena,
						(process->pc + val[i]) & 0xFFF, 4);
			i++;
		}
		sum = val[0] + val[1];
		process->carry = (sum == 0 ? 1 : 0);
		process->registre[val[2]] = big_end_toi(vm->arena.arena,
				process->pc + sum & 0xFFF, 4);
	}
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

void			op_lfork(t_vm *vm, t_process *process)
{
	int		n_proc;
	int		old_proc;

	n_proc = vm->arena.nbr_process;
	if (n_proc == vm->arena.s_proc)
	{
		old_proc = process->number;
		if (!(vm->arena.process = realloc(vm->arena.process,
					sizeof(t_process) * (vm->arena.s_proc * 2))))
			error_exit(vm, "Error: new process allocation failed");
		vm->arena.s_proc *= 2;
		process = &vm->arena.process[old_proc - 1];
	}
	ft_memcpy((t_process *)&(vm->arena.process[n_proc]), (t_process*)process,\
			sizeof(t_process));
	vm->arena.process[n_proc].pc = (process->pc +\
			process->instruction.value[0]) & 0xFFF;
	vm->arena.process[n_proc].number = n_proc;
	vm->arena.process[n_proc].instruction.op_code = 0;
	vm->arena.process[n_proc].lives_since_check = 0;
	(vm->arena.nbr_process)++;
	(vm->arena.nbr_process_alive)++;
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

void			op_aff(t_vm *vm, t_process *process)
{
	t_arg_type	*type;
	int			val;

	type = process->instruction.types;
	if (type[0] != -1)
	{
		val = process->instruction.value[0];
		ft_printf("%c", (char)(process->registre[val]));
	}
	vm->arena.arena_owner[process->pc] *= -1;
	process->pc = (process->pc + process->instruction.adv) % MEM_SIZE;
	vm->arena.arena_owner[process->pc] *= -1;
}

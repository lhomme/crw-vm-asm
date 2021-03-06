/*
** home_vm.c for home_vm in /home/kyndt/crw-vm-asm/vm/vm_apply
** 
** Made by clovis kyndt
** Login   <kyndt_c@epitech.net>
** 
** Started on  Thu Mar 22 21:27:16 2012 clovis kyndt
** Last update Sun Mar 25 22:29:38 2012 pierre ecormier
*/

#include        "op.h"
#include        "corewar.h"
#include        "vm_funcs.h"

int             dedi_no_tab(t_champ *tmp, t_arena *arena,
			    int *i,
			    void (*act_fct[16])(t_arena *arena, t_champ *champ,
						char type[4], int argv[4]))
{
  int           arg[4];
  char          type[4];
  int           nb;
  int           ptr_i;

  ptr_i = VM_BORD(*i + 1);
  if (arena->index > 0)
    {
      nb = (arena->map)[VM_BORD(ptr_i)];
      nb = select_oct(type, nb);
      type_exp(arena->act, type);
      ptr_i++;
      print_my_arg(arena->map, &ptr_i, arg, nb, type);
    }
  else if (!(arena->index))
    print_my_arg_spec_eval(arena->map, &ptr_i, arg, arena->act);
  nb = (arena->map)[*i] - 1;
  if (nb < 16 && nb >= 0)
    (act_fct[nb])(arena, tmp, type, arg);
  if (arena->act != ZJMP || tmp->carry == 0)
    tmp->pc = ptr_i;
  return (0);
}

int             cycle_action(t_arena *arena,
			     void (*act_fct[16])(t_arena *arena,
						 t_champ *champ, char type[4], int argv[4]), int cycle)
{
  int           i;
  t_champ       *champ;
  char          *mem;
  int		max;
  int           time_act;

  champ = arena->champs;
  mem = arena->map;
  max = -1;
  while (champ != NULL)
    {
      i = champ->pc;
      time_act = time_action(mem[i]);
      if (max == -1 || time_act < max)
	max = time_act;
      if ((champ->cycle + time_act) <= cycle && mem[i] >= 0 && mem[i] < 16)
        {
          arena->index = decript_type(mem[i]);
	  arena->act = mem[i];
	  dedi_no_tab(champ, arena, &i, act_fct);
          champ->cycle = cycle;
        }
      champ = champ->next;
    }
  return (max);
}

void            home_vm(t_arena *arena, t_args_events *args)
{
  int           cycle;
  int		tmp;
  int           cycle_m;
  void          (*act_fct[16])(t_arena *arena,
			       t_champ *champ, char type[4], int argv[4]);

  init_fct_tab(act_fct, &cycle_m, arena);
  while (champ_count(arena->champs) > 1)
    {
      cycle = init_bc_vm(arena);
      while (cycle < arena->cycle_to_die && arena->nb_live < NBR_LIVE)
        {
          tmp = cycle_action(arena, act_fct, cycle);
	  do_refresh(args);
	  cycle++;
	  arena->cycle_tmp++;
	  if (arena->cycle_tmp == arena->cycle_max)
	    dump_mem(arena->map);
        }
      if (arena->nb_live >= NBR_LIVE)
        arena->cycle_to_die -= CYCLE_DELTA;
      champ_count(arena->champs);
      kill_champ(arena);
    }
  aff_rendu(arena);
}

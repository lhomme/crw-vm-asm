/*
** expose.c for wolf in /home/boell_g//Documents/projets/wolf
** 
** Made by guillaume boell
** Login   <boell_g@epitech.net>
** 
** Started on  Fri Jan 13 11:00:18 2012 guillaume boell
** Last update Sun Mar 25 16:49:06 2012 guillaume boell
*/
#include <math.h>
#include "corewar.h"
#include "minilibx/mlx.h"
#include "op.h"

int	gere_expose(t_args_events *args)
{
  int	didonce;

  didonce = 0;
  if (!didonce)
    home_vm(args->arena, args);
  didonce = 1;
  mlx_put_image_to_window(args->id_aff, args->id_fenetre, args->img_ptr, 0, 0);
  return (0);
}

int	get_pc_col(t_champ *champs, t_col *col, int i, t_col c)
{
  c.r = c.g = c.b = 0;
  if (i == champs->pc)
    c.r = 127;
  if ((champs = champs->next) != NULL)
    {
      if (champs && i == champs->pc)
	c.b = 127;
      if ((champs = champs->next) != NULL)
	{
	  if (champs && i == champs->pc)
	    c.g = 127;
	  if ((champs = champs->next) != NULL)
	    {
	      if (champs && i == champs->pc)
		c.g = c.b = 127;
	    }
	}
    }
  if ((((c.r == c.g) == c.b) == 0))
    return (0);
  col->r = c.r;
  col->g = c.g;
  col->b = c.b;
  return (1);
}

void	get_color(t_col *col, int i, t_arena *arena)
{
  t_col	temp;

  if (!get_pc_col(arena->champs, col, i, temp))
    {
      col->r = arena->map[i] * 10;
      col->g = arena->map[i] * 10;
      col->b = arena->map[i] * 10;
    }
}

void	refresh(t_args_events *args)
{
  int	i;
  int	n;
  t_col	color;
  t_pos	pos;
  int	taille;

  i = n = 0;
  taille = LARG / sqrt(MEM_SIZE);
  while (i < MEM_SIZE)
    {
      pos.x = (n * taille) % (LARG - taille);
      pos.y = ((i * taille) / (LARG - taille)) * taille;
      get_color(&color, i, args->arena);
      do_carre(args, taille, &pos, &color);
      i++;
      n++;
      if (LARG / taille <= n)
	n = 0;
    }
}

int	key_hook(int keycode, t_args_events *args)
{
  args = args;
  if (keycode == 65307)
    exit(0);
  return (0);
}

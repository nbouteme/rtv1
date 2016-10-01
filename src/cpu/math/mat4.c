/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 12:45:54 by nbouteme          #+#    #+#             */
/*   Updated: 2016/10/01 14:13:04 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/math.h>

void	mat_invcoef(t_mat4 m, float coefs[])
{
	coefs[0] = m.v[2][2] * m.v[3][3] - m.v[3][2] * m.v[2][3];
	coefs[1] = m.v[1][2] * m.v[3][3] - m.v[3][2] * m.v[1][3];
	coefs[2] = m.v[1][2] * m.v[2][3] - m.v[2][2] * m.v[1][3];
	coefs[3] = m.v[2][1] * m.v[3][3] - m.v[3][1] * m.v[2][3];
	coefs[4] = m.v[1][1] * m.v[3][3] - m.v[3][1] * m.v[1][3];
	coefs[5] = m.v[1][1] * m.v[2][3] - m.v[2][1] * m.v[1][3];
	coefs[6] = m.v[2][1] * m.v[3][2] - m.v[3][1] * m.v[2][2];
	coefs[7] = m.v[1][1] * m.v[3][2] - m.v[3][1] * m.v[1][2];
	coefs[8] = m.v[1][1] * m.v[2][2] - m.v[2][1] * m.v[1][2];
	coefs[9] = m.v[2][0] * m.v[3][3] - m.v[3][0] * m.v[2][3];
	coefs[10] = m.v[1][0] * m.v[3][3] - m.v[3][0] * m.v[1][3];
	coefs[11] = m.v[1][0] * m.v[2][3] - m.v[2][0] * m.v[1][3];
	coefs[12] = m.v[2][0] * m.v[3][2] - m.v[3][0] * m.v[2][2];
	coefs[13] = m.v[1][0] * m.v[3][2] - m.v[3][0] * m.v[1][2];
	coefs[14] = m.v[1][0] * m.v[2][2] - m.v[2][0] * m.v[1][2];
	coefs[15] = m.v[2][0] * m.v[3][1] - m.v[3][0] * m.v[2][1];
	coefs[16] = m.v[1][0] * m.v[3][1] - m.v[3][0] * m.v[1][1];
	coefs[17] = m.v[1][0] * m.v[2][1] - m.v[2][0] * m.v[1][1];
}

void	make_faces(float *coefs, t_vec4 faces[6])
{
	int i;

	i = -1;
	while (++i < 6)
		faces[i].s = (t_4dvec){ coefs[i * 3],
								coefs[i * 3],
								coefs[i * 3 + 1],
								coefs[i * 3 + 2] };
}

void	make_vecs(t_mat4 m, t_vec4 vec[4])
{
	int i;

	i = -1;
	while (++i < 4)
		vec[i].s = (t_4dvec){ m.v[1][i], m.v[0][i], m.v[0][i], m.v[0][i] };
}

void	make_inv(t_vec4 inv[4], t_vec4 vec[4], t_vec4 faces[6], t_vec4 sign[2])
{
	inv[0] = vec4_add(vec4_sub(vec4_mul(vec[1], faces[0]),
							vec4_mul(vec[2], faces[1])),
					vec4_mul(vec[3], faces[2]));
	inv[1] = vec4_add(vec4_sub(vec4_mul(vec[0], faces[0]),
							vec4_mul(vec[2], faces[3])),
					vec4_mul(vec[3], faces[4]));
	inv[2] = vec4_add(vec4_sub(vec4_mul(vec[0], faces[1]),
							vec4_mul(vec[1], faces[3])),
					vec4_mul(vec[3], faces[5]));
	inv[3] = vec4_add(vec4_sub(vec4_mul(vec[0], faces[2]),
							vec4_mul(vec[1], faces[4])),
					vec4_mul(vec[2], faces[5]));
	sign[0].s = (t_4dvec){+1, -1, +1, -1};
	sign[1].s = (t_4dvec){-1, +1, -1, +1};
}

/*
**  t_vec4 faces[6]; // lenny[0]
**t_vec4 vec[4]; // lenny[1]
**t_vec4 inv[4]; // lenny[2]
**t_vec4 sign[2]; // lenny[3]
**t_vec4 dot; // lenny[4]
**t_vec4 row; // lenny[5]
*/

t_mat4	mat4_inverse(t_mat4 m)
{
	int		i;
	float	coefs[18];
	t_vec4	lenny[6][6];
	t_mat4	inverse;
	float	det;

	mat_invcoef(m, coefs);
	make_faces(coefs, lenny[0]);
	make_vecs(m, lenny[1]);
	make_inv(lenny[2], lenny[1], lenny[0], lenny[3]);
	i = -1;
	while (++i < 4)
	{
		inverse.s.v[i] = vec4_mul(lenny[2][i], lenny[3][i % 2]).s;
		lenny[5][0].v[i] = lenny[2][i].v[0];
	}
	lenny[4][0] = vec4_mul(m.s.v[0], lenny[5][0]);
	det = lenny[4][0].s.x + lenny[4][0].s.y + lenny[4][0].s.z + lenny[4][0].s.w;
	return (mat4_muls(inverse, 1.0f / det));
}

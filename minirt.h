#ifndef MINIRT_H
#define MINIRT_H

typedef struct s_ambient
{
	int light_ratio;
	int color;

} t_ambient;

typedef struct s_vector
{
	float x;
	float y;
	float z;
} t_vector;

//field of view: size of the viewport and how far away they are from camera
typedef struct s_camera
{
	int coordinates;
	t_vector orientation;
	int fov;

} t_camera;

typedef struct s_light
{
	int amb_ratio;

} t_light;

typedef struct s_sp
{
	int amb_ratio;

} t_sp;

typedef struct s_pl
{
	int amb_ratio;

} t_pl;

typedef struct s_cy
{
	int amb_ratio;

} t_cy;

#endif

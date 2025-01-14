#ifndef MINIRT_H
#define MINIRT_H

typedef struct s_vector
{
	float x;
	float y;
	float z;
} t_vector;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
} t_color;

typedef struct s_point
{
	float x;
	float y;
	float z;
} t_point;

typedef struct s_ambient
{
	int light_ratio;
	t_color color;

} t_ambient;

//FOV: Angle of what you see.
typedef struct s_camera
{
	t_point viewpoint;
	t_vector orientation;
	int fov;

} t_camera;

typedef struct s_light
{
	t_point light_point;
	int diameter;
	t_color color;
} t_light;

typedef struct s_sp
{
	t_point center;
	float diameter;
	t_color color;
} t_sp;

typedef struct s_pl
{
	t_point plane_point;
	t_vector normal_vector;
	t_color color;

} t_pl;

typedef struct s_cy
{
	t_point center;
	t_vector axis;
	float diameter;
	float height;
	t_color;

} t_cy;

typedef struct s_scene
{
	void	*mlx_ptr;
	void	*win;
} t_scene;


#endif

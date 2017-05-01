#include "BSPTree.h"
#include "Object_Collections.h"


BSPTree::BSPTree() : root(nullptr), min_point(-10, -10, -10), max_point(50, 50, 50), box(min_point, max_point)
{
}

BSPTree::BSPTree(vector3<double> in_min_point, vector3<double> in_max_point) : root(nullptr), min_point(in_min_point), max_point(in_max_point), box(min_point, max_point)
{

}

BSPTree::~BSPTree()
{
}

void BSPTree::build_tree()
{
	root = new BSPTree_Node(min_point, max_point);
	root->cut = 0;
	for (int i = 0; i < objects.size(); i++)
	{
		root->object_list.push_back(i);
	}
	sub_divide(root, 0);
}

void BSPTree::sub_divide(BSPTree_Node* parent, int current_depth)
{
	if (parent->object_list.size() <= leaf_object_num || current_depth > depth_limit)       //递归终止条件
	{
		return;
	}
	parent->left_child = new BSPTree_Node((parent->box).min_point, (parent->box).max_point);
	parent->right_child = new BSPTree_Node((parent->box).min_point, (parent->box).max_point);
	if (parent->cut == 0)           //cut with x-axis
	{
		(parent->left_child->box).max_point.x = ((parent->box).min_point.x + (parent->box).max_point.x) / 2;
		(parent->right_child->box).min_point.x = (parent->left_child->box).max_point.x;
		parent->left_child->cut = 1;
		parent->right_child->cut = 1;
	}
	else if (parent->cut == 1)            //cut with y-axis
	{
		(parent->left_child->box).max_point.y = ((parent->box).min_point.y + (parent->box).max_point.y) / 2;
		(parent->right_child->box).min_point.y = (parent->left_child->box).max_point.y;
		parent->left_child->cut = 2;
		parent->right_child->cut = 2;
	}
	else                                  //cut with z-axis
	{
		(parent->left_child->box).max_point.z = ((parent->box).min_point.z + (parent->box).max_point.z) / 2;
		(parent->right_child->box).min_point.z = (parent->left_child->box).max_point.z;
		parent->left_child->cut = 0;
		parent->right_child->cut = 0;
	}
	//then produce object list of child
	for (int i = 0; i < (parent->object_list).size(); i++)
	{
		Object *current_object = objects[parent->object_list[i]];     //判断current_object位于左儿子还是右儿子
		if (current_object->object_type == 4)      //plane
		{
			Plane* current_plane = dynamic_cast<Plane*>(current_object);
			if (BoundingBox::plane_aabb_overlap(current_plane->A, current_plane->B, current_plane->C, current_plane->D, (parent->left_child->box).min_point, (parent->left_child->box).max_point))     //若plane在左儿子内，将其加入左儿子
			{
				(parent->left_child->object_list).push_back(parent->object_list[i]);
			}
			if (BoundingBox::plane_aabb_overlap(current_plane->A, current_plane->B, current_plane->C, current_plane->D, (parent->right_child->box).min_point, (parent->right_child->box).max_point))         //若plane在右儿子内，将其加入右儿子
			{
				(parent->right_child->object_list).push_back(parent->object_list[i]);
			}
		}
		else if (current_object->object_type == 3)       //sphere
		{
			Sphere* current_sphere = dynamic_cast<Sphere*>(current_object);
			if (BoundingBox::sphere_aabb_overlap(current_sphere->sphere_center, current_sphere->radius, (parent->left_child->box).min_point, (parent->left_child->box).max_point))
			{
				(parent->left_child->object_list).push_back(parent->object_list[i]);
			}
			if (BoundingBox::sphere_aabb_overlap(current_sphere->sphere_center, current_sphere->radius, (parent->right_child->box).min_point, (parent->right_child->box).max_point))
			{
				(parent->right_child->object_list).push_back(parent->object_list[i]);
			}
		}
		else if (current_object->object_type == 1)          //triangle
		{
			Triangle* current_triangle = dynamic_cast<Triangle*>(current_object);
			if (BoundingBox::triangle_aabb_overlap(current_triangle->vertex[0], current_triangle->vertex[1], current_triangle->vertex[2], (parent->left_child->box).min_point, (parent->left_child->box).max_point))
			{
				(parent->left_child->object_list).push_back(parent->object_list[i]);
			}
			if (BoundingBox::triangle_aabb_overlap(current_triangle->vertex[0], current_triangle->vertex[1], current_triangle->vertex[2], (parent->right_child->box).min_point, (parent->right_child->box).max_point))
			{
				(parent->right_child->object_list).push_back(parent->object_list[i]);
			}
		}
		else if (current_object->object_type == 0)           //aabb
		{
			BoundingBox* current_aabb = dynamic_cast<BoundingBox*>(current_object);
			if (BoundingBox::aabb_aabb_overlap(current_aabb->min_point, current_aabb->max_point, (parent->left_child->box).min_point, (parent->left_child->box).max_point))
			{
				(parent->left_child->object_list).push_back(parent->object_list[i]);
			}
			if (BoundingBox::aabb_aabb_overlap(current_aabb->min_point, current_aabb->max_point, (parent->right_child->box).min_point, (parent->right_child->box).max_point))
			{
				(parent->right_child->object_list).push_back(parent->object_list[i]);
			}
		}
		else                              //others，将其放在两个子物体中
		{
			(parent->left_child->object_list).push_back(parent->object_list[i]);
			(parent->right_child->object_list).push_back(parent->object_list[i]);
		}
	}
	sub_divide(parent->left_child, current_depth + 1);
	sub_divide(parent->right_child, current_depth + 1);
}

bool BSPTree::intersect_point(Ray input_ray, int &object_index, vector3<double> &point)
{
	double t_min, t_max;
	if (box.intersect(input_ray, point, t_min, t_max))
	{
		return RayTreeIntersect(input_ray, root, t_min - limit_zero, t_max + limit_zero, point, object_index);
	}
	else
	{
		return false;
	}
}

bool BSPTree::RayTreeIntersect(Ray input_ray, BSPTree_Node* tree_node, double _min, double _max, vector3<double> &point, int &index)
{
	if (tree_node == nullptr)             //won't reach
	{
		return false;
	}
	if (tree_node->left_child == nullptr && tree_node->right_child == nullptr)         //tree_node is a leaf
	{                        //ray可能与leaf_tree_node相交，也可能不与leaf_tree_node相交，距离大于max时应该舍弃，否则交点不在该aabb内
		bool intersect_flag = false;           //若相交，flag为true
		double closest_distance = 100000000;           //存储最近的距离
		for (int i = 0; i < (tree_node->object_list.size()); i++)
		{
			vector3<double> temp_point;
			if (objects[(tree_node->object_list[i])]->intersect(input_ray, temp_point))
			{
				vector3<double> diff = temp_point - input_ray.start_point;
				if (diff.length < _max + limit_zero)             //在aabb内物体与光线相交
				{
					intersect_flag = true;
					if (diff.length < closest_distance)           //找到了更近的点
					{
						closest_distance = diff.length;
						index = tree_node->object_list[i];
						point = temp_point;
					}
				}
			}
		}
		return intersect_flag;
	}
	Plane* cut_plane;
	BSPTree_Node* near;
	BSPTree_Node* far;
	if (tree_node->cut == 0)        //cut with x_axis
	{
		cut_plane = new Plane(((tree_node->box).min_point + (tree_node->box).max_point) / 2, vector3<double>(1, 0, 0));
		if (fabs(input_ray.start_point.x - (cut_plane->passed_point).x) < limit_zero)
		{
			if (input_ray.direction.x > 0)          //向上射出right为远端，否则right为近端
			{
				return RayTreeIntersect(input_ray, tree_node->right_child, 0, _max, point, index);
			}
			else
			{
				return RayTreeIntersect(input_ray, tree_node->left_child, 0, _max, point, index);
			}
		}
		else
		{
			if (input_ray.start_point.x > (cut_plane->passed_point).x)
			{
				near = tree_node->right_child;
				far = tree_node->left_child;
			}
			else
			{
				near = tree_node->left_child;
				far = tree_node->right_child;
			}
		}
	}
	else if (tree_node->cut == 1)            //cut with y_axis
	{
		cut_plane = new Plane(((tree_node->box).min_point + (tree_node->box).max_point) / 2, vector3<double>(0, 1, 0));
		if (fabs(input_ray.start_point.y - (cut_plane->passed_point).y) < limit_zero)
		{
			if (input_ray.direction.y > 0)          //向上射出right为远端，否则right为近端
			{
				return RayTreeIntersect(input_ray, tree_node->right_child, 0, _max, point, index);
			}
			else
			{
				return RayTreeIntersect(input_ray, tree_node->left_child, 0, _max, point, index);
			}
		}
		else
		{
			if (input_ray.start_point.y > (cut_plane->passed_point).y)
			{
				near = tree_node->right_child;
				far = tree_node->left_child;
			}
			else
			{
				near = tree_node->left_child;
				far = tree_node->right_child;
			}
		}
	}
	else                 //cut with z_axis
	{
		cut_plane = new Plane(((tree_node->box).min_point + (tree_node->box).max_point) / 2, vector3<double>(0, 0, 1));
		if (fabs(input_ray.start_point.z - (cut_plane->passed_point).z) < limit_zero)
		{
			if (input_ray.direction.z > 0)          //向上射出right为远端，否则right为近端
			{
				return RayTreeIntersect(input_ray, tree_node->right_child, 0, _max, point, index);
			}
			else
			{
				return RayTreeIntersect(input_ray, tree_node->left_child, 0, _max, point, index);
			}
		}
		else
		{
			if (input_ray.start_point.z > (cut_plane->passed_point).z)
			{
				near = tree_node->right_child;
				far = tree_node->left_child;
			}
			else
			{
				near = tree_node->left_child;
				far = tree_node->right_child;
			}
		}
	}
	double dis = cut_plane->signed_distance(input_ray);
	delete cut_plane;
	if (dis > _max + limit_zero || dis < -1 * limit_zero)              //whole interval is on near side
	{
		return RayTreeIntersect(input_ray, near, _min, _max, point, index);
	}
	else if (dis < _min - limit_zero)               //whole interval is on far side
	{
		return RayTreeIntersect(input_ray, far, _min, _max, point, index);
	}
	else
	{
		if (RayTreeIntersect(input_ray, near, _min, dis, point, index))
		{
			return true;
		}
		else             //don't intercept with near aabb
		{
			return RayTreeIntersect(input_ray, far, dis, _max, point, index);
		}
	}
}
#include "kdTree.h"
#include <algorithm>

double getvalue(photon input, int dimension)
{
	if (dimension == 0)
	{
		return input.photon_ray.start_point.x;
	}
	else if (dimension == 1)
	{
		return input.photon_ray.start_point.y;
	}
	else if (dimension == 2)
	{
		return input.photon_ray.start_point.z;
	}
}

bool compare_x(photon a, photon b) { return a.photon_ray.start_point.x < b.photon_ray.start_point.x; }
bool compare_y(photon a, photon b) { return a.photon_ray.start_point.y < b.photon_ray.start_point.y; }
bool compare_z(photon a, photon b) { return a.photon_ray.start_point.z < b.photon_ray.start_point.z; }
/*void quickSelect(vector<photon>& photon_array, int k, int dimension, int low, int high)
{
	for (int lo = low, hi = high - 1; lo < hi; )
	{
		int i = lo, j = hi;
		photon pivot = photon_array[lo];
		while (i < j)
		{
			while ((i < j) && (getvalue(pivot, dimension) <= getvalue(photon_array[j], dimension)))
			{
				j--;
			}
			photon_array[i] = photon_array[j];
			while ((i < j) && (getvalue(photon_array[i], dimension) <= getvalue(pivot, dimension)))
			{
				i++;
			}
			photon_array[j] = photon_array[i];
		}
		assert(i == j);
		photon_array[i] = pivot;
		if (k <= i)
		{
			hi = i - 1;
		}
		if (i <= k)
		{
			lo = i + 1;
		}
	}
}*/

kdTree::kdTree(vector<photon> photon_array)
{
	root = build_kdTree(photon_array, 0, 0, photon_array.size());
}


kdTree::~kdTree()
{
}

kd_node* kdTree::build_kdTree(vector<photon>& photon_array, int depth, int left_bound, int right_bound)
{
	if (right_bound == left_bound + 1)
	{
		return create_leaf(photon_array[left_bound]);
	}
	else if (right_bound <= left_bound)
	{
		return nullptr;
	}
	int split_direction = depth % 3;
	if (split_direction == 0)
	{
		std::nth_element(photon_array.begin() + left_bound, photon_array.begin() + (left_bound + right_bound) / 2, photon_array.begin() + right_bound, compare_x);
	}
	else if (split_direction == 1)
	{
		std::nth_element(photon_array.begin() + left_bound, photon_array.begin() + (left_bound + right_bound) / 2, photon_array.begin() + right_bound, compare_y);
	}
	else
	{
		std::nth_element(photon_array.begin() + left_bound, photon_array.begin() + (left_bound + right_bound) / 2, photon_array.begin() + right_bound, compare_z);
	}
	kd_node* current_node = new kd_node(photon_array[(left_bound + right_bound) / 2]);
	current_node->axis = split_direction;
	current_node->left_child = build_kdTree(photon_array, depth + 1, left_bound, (left_bound + right_bound) / 2);
	current_node->right_child = build_kdTree(photon_array, depth + 1, (left_bound + right_bound) / 2 + 1, right_bound);
	return current_node;
}

kd_node* kdTree::create_leaf(photon input_photon)
{
	kd_node* temp_node = new kd_node(input_photon);
	return temp_node;             //因为是叶节点，所以axis可以赋任意值
}

k_collection kdTree::knn(vector3<double> target)
{
	k_collection nearest_collection(k_size);
	double position[3];
	position[0] = target.x, position[1] = target.y, position[2] = target.z;
	nearest(root, position, nearest_collection);
	return nearest_collection;
}

double kdTree::distance(double* a, double* b)
{
	double value = 0;
	for (int i = 0; i < 3; i++)
	{
		value += (a[i] - b[i]) * (a[i] - b[i]);
	}
	return sqrt(value);
}
void kdTree::nearest(kd_node* current, double* target, k_collection& collection)
{
	double target_distance = distance(target, current->position);
	collection.add_node(current, target_distance);
	double median = current->position[current->axis];
	double value = target[current->axis];
	if (value <= median)
	{           //在超平面的左侧
		if (current->left_child != nullptr)
		{
			nearest(current->left_child, target, collection);
		}
		if (current->right_child != nullptr && fabs(value - median) <= collection.max_value)
		{
			nearest(current->right_child, target, collection);
		}
	}
	else        //在超平面的右侧
	{
		if (current->right_child != nullptr)
		{
			nearest(current->right_child, target, collection);
		}
		if (current->left_child != nullptr && fabs(value - median) <= collection.max_value)
		{
			nearest(current->left_child, target, collection);
		}
	}
}
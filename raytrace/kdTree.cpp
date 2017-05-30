#include "kdTree.h"

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

void quickSelect(vector<photon>& photon_array, int k, int dimension)
{
	for (int lo = 0, hi = photon_array.size() - 1; lo < hi; )
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
}

kdTree::kdTree(vector<photon>& photon_array)
{
	root = build_kdTree(photon_array, 0);
}


kdTree::~kdTree()
{
}

kd_node* kdTree::build_kdTree(vector<photon> photon_array, int depth)
{
	if (photon_array.size() == 1)
	{
		return create_leaf(photon_array[0]);
	}
	int split_direction = depth % 3;
	/*cout << "begin" << endl;
	for (int i = 0; i < photon_array.size(); i++)
	{
		cout << photon_array[i].photon_ray.start_point << endl;
	}*/
	quickSelect(photon_array, photon_array.size() / 2, split_direction);
	/*cout << "axis " << split_direction << endl;
	for (int i = 0; i < photon_array.size(); i++)
	{
		cout << photon_array[i].photon_ray.start_point << endl;
	}*/
	kd_node* current_node = new kd_node(photon_array[photon_array.size() / 2]);
	current_node->axis = split_direction;
	vector<photon> left_photon_array;            //左孩子的点集
	vector<photon> right_photon_array;           //右孩子的点集
	for (int i = 0; i < photon_array.size() / 2; i++)
	{
		left_photon_array.push_back(photon_array[i]);
	}
	for (int i = (photon_array.size() / 2) + 1; i < photon_array.size(); i++)
	{
		right_photon_array.push_back(photon_array[i]);
	}
	if (left_photon_array.size() > 0)
	{
		current_node->left_child = build_kdTree(left_photon_array, depth + 1);
	}
	if (right_photon_array.size() > 0)
	{
		current_node->right_child = build_kdTree(right_photon_array, depth + 1);
	}
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
	return value;
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
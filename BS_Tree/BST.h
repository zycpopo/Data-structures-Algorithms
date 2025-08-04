#pragma once
template<class K,class V>
struct BSTNode
{
	K _key;
	BSTNode<K>* _left;
	BSTNode<K>* _right;
	BSTNode(const K& key)
		:_key(key)
		, _left(nullptr)
		, _right(nullptr)
	{}
};
template<class K>
class BSTree
{
	typedefBSTNode<K> Node;
public:
	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(key);
		if (parent->_key < key)
		{
			parent->right = cur;
		}
		else
		{
			parent->_left = cur;
		}

		return true;
	}

	bool Erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
			cur = cur->_right;
			}
			else {
				if (cur->_left == nullptr)
				{
					if (parent == nullptr)
					{
						_root = cur->_right;
					}

					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;
						}
					}
					delete cur;
					return true;
				}
				else if(cur->_right==nullptr)
				{
					if (parent == nullptr)
					{
						_root = cur->_left;
					}
	
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
					delete cur;
					return true;
				}
				else//这个就是节点左右节点都存在，采用替换法
				{
					Node* rightMinP = cur;
					Node* rightMin = cur->_right;
					while (rightMin->_left)
					{
						rightMinP = rightMin;
						rightMin = rightMin->_left;
					}
					cur->_key = rightMin->_key;
					if (rightMinP->_left == rightMin)
						rightMinP->_left = rightMin->_right;
					else
						rightMinP->_right = rightMin->_right;
					delete rightMin;
					return true;
				}
			}
		}
		return false;
	}

	bool Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->left;
			}
			else if (cur->_key < key)
			{
				cur = cur->right;
			}
			else
			{
				return true;
			}
		}

		return false;
	}

	void InOrder()
	{
		_InOrder(_root);
		count << endl;
	}
private:
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		InOrder(root->left);
		count << root->key << "";
		_InOrder(root->right);
	}
private:
	Node* _root = nullptr;
};
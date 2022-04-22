#pragma once
#include <iostream>
#include <queue>

template <typename tData>
class BinarySearchTree
{
private:
	struct TreeNode {
		tData val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(const tData& _val) : val(_val), left(nullptr), right(nullptr) {

		}
	};

	TreeNode* root;
	int diameter;

	TreeNode* InsertIntoTree(TreeNode* root, const tData& val) {

		if (root == nullptr) {
			return new TreeNode(val);
		}

		if (root->val > val) {
			root->left = InsertIntoTree(root->left, val);
		}
		else if(root->val < val) {
			root->right = InsertIntoTree(root->right, val);
		}

		return root;

	}
	
	void InorderTraverse(TreeNode* root) {
		if (root == nullptr) {
			return;
		}
		InorderTraverse(root->left);
		std::cout << root->val << "\n";
		InorderTraverse(root->right);
	}

	TreeNode* FindInTree(TreeNode* root, const tData& val) {

		if (root == nullptr) {
			return root;
		}

		if (root->val > val) {
			return FindInTree(root->left, val);
		}
		else if (root->val < val) {
			return FindInTree(root->right, val);
		}

		return root;
	}

	TreeNode* FindMin(TreeNode* root) {
		if (root == nullptr) {
			return root;
		}

		TreeNode* current = root;
		while (current->left != nullptr) {
			current = current->left;
		}

		return current;
	}

	TreeNode* InorderSuccessor(TreeNode* root, const tData& val) {

		TreeNode* current = FindInTree(root, val);
		if (current == nullptr) {
			return current;
		}

		if (current->right != nullptr) {
			return FindMin(current->right);
		}
		else {
			TreeNode* ancestor = root;
			TreeNode* successor = nullptr;

			while (ancestor != current) {

				if (ancestor->val > current->val) {
					successor = ancestor;
					ancestor = ancestor->left;
				}
				else {
					ancestor = ancestor->right;
				}

			}

			return successor;
		}

	}

	void LevelOrder(TreeNode* root, std::vector<std::vector<tData>>& result) {

		if (root == nullptr) {
			return;
		}

		std::queue<TreeNode*> nodeQueue;

		nodeQueue.push(root);

		while (!nodeQueue.empty())
		{
			std::vector<tData> currentLevel;
			int levelSize = nodeQueue.size();

			for (int i = 0; i < levelSize; i++) {

				TreeNode* current = nodeQueue.front();
				nodeQueue.pop();

				currentLevel.push_back(current->val);

				if (current->left != nullptr) {
					nodeQueue.push(current->left);
				}

				if (current->right != nullptr) {
					nodeQueue.push(current->right);
				}

			}

			result.push_back(currentLevel);

		}

	}

	bool isIdentical(TreeNode* root, TreeNode* otherRoot) {

		if (root == nullptr && otherRoot == nullptr) {
			return true;
		}
		else if (root == nullptr && otherRoot != nullptr) {
			return false;
		}
		else if (root != nullptr && otherRoot == nullptr) {
			return false;
		}
		else {

			if (root->val == otherRoot->val && isIdentical(root->left, otherRoot->left) && isIdentical(root->right, otherRoot->right)) {
				return true;
			}
			else {
				return false;
			}

		}
	}

	TreeNode* Invert(TreeNode* root) {

		if (root == nullptr) {
			return root;
		}

		TreeNode* temp = root->left;
		root->left = root->right;
		root->right = temp;

		root->left = Invert(root->left);
		root->right = Invert(root->right);

		return root;
	}

	TreeNode* DeleteFromBST(TreeNode* root, const tData& val) {

		if (root == nullptr) {
			return root;
		}
		if (root->val > val) {
			root->left = DeleteFromBST(root->left, val);
		}
		else if (root->val < val) {
			root->right = DeleteFromBST(root->right, val);
		}
		else {
			if (root->left == nullptr && root->right == nullptr) {
				delete root;
				root = nullptr;
			}
			else if (root->left == nullptr) {
				TreeNode* temp = root;
				root = root->right;
				delete temp;
			}
			else if (root->right == nullptr) {
				TreeNode* temp = root;
				root = root->left;
				delete temp;
			}
			else {

				TreeNode* temp = FindMin(root->right);
				root->val = temp->val;
				root->right = DeleteFromBST(root->right, temp->val);
			}
		}
		return root;
	}

	int HeightOfTree(TreeNode* root) {

		if (root == nullptr) {
			return 0;
		}

		return std::max(HeightOfTree(root->left), HeightOfTree(root->right)) + 1;

	}

	int DiameterOfTree(TreeNode* root, int& diameter) {

		if (root == nullptr) {
			return -1;
		}

		int leftTreeHeight = DiameterOfTree(root->left, diameter);
		int rightTreeHeight = DiameterOfTree(root->right, diameter);

		diameter = std::max(diameter, leftTreeHeight + rightTreeHeight + 2);

		int height = std::max(leftTreeHeight, rightTreeHeight) + 1;

		return height;
	}

public:
	BinarySearchTree() {
		root = nullptr;
		diameter = 0;
	}

	void Insert(const tData& val) {
		root = InsertIntoTree(root, val);
	}

	void Inorder() {
		InorderTraverse(root);
	}

	bool Find(const tData& val) {
		TreeNode* node = FindInTree(root, val);
		if (node != nullptr) {
			std::cout << "Found:" << node->val << "\n";
			return true;
		}
		else {
			std::cout << "Not Found \n";
			return false;
		}
	}

	void InorderSuccessorValue(const tData& val) {
		TreeNode* node = InorderSuccessor(root, val);
		if (node == nullptr) {
			std::cout << "Value not found \n";
		}
		else {
			std::cout << "Value is:" << node->val << "\n";
		}
	}

	void LevelOrderTraversal(std::vector<std::vector<tData>>& result) {
		LevelOrder(root, result);
	}

	void Delete(const tData& val) {
		root = DeleteFromBST(root, val);
	}

	int Height() {
		return HeightOfTree(root);
	}

	int Diameter() {
		DiameterOfTree(root, diameter);
		return diameter;
	}

};

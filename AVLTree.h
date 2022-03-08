#pragma once
#include <iostream>

template<typename tData>
class AVLTree {
private:
	struct TreeNode {
		tData val;
		TreeNode* left;
		TreeNode* right;
		int height;

	};

	TreeNode* root;

public:
	AVLTree() {
		root = nullptr;
	}

private:

	TreeNode* createNewNode(const tData& _val) {
		TreeNode* newNode = new TreeNode();
		newNode->val = _val;
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->height = 1;
		return newNode;
	}

	int getHeight(TreeNode* node) {
		if (node == nullptr) {
			return 0;
		}
		return node->height;
	}

	int getBalanceFactor(TreeNode* node) {
		if (node == nullptr) {
			return 0;
		}

		return (getHeight(node->left) - getHeight(node->right));
	}

	TreeNode* getMinNode(TreeNode* root) {
		TreeNode* current = root;
		if (current == nullptr) {
			return current;
		}

		while (current->left != nullptr) {
			current = current->left;
		}

		return current;
	}

	TreeNode* rightRotate(TreeNode* y) {
		TreeNode* x = y->left;
		y->left = x->right;
		x->right = y;

		//Since x is the new root and y its right child it is imperative we update the child's height aka y's height first!
		y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
		x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
		return x;
	}

	TreeNode* leftRotate(TreeNode* x) {
		TreeNode* y = x->right;
		x->right = y->left;
		y->left = x;

		//since y is the root and x the child we update x's height first!
		x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
		y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
		return y;
	}

	TreeNode* InsertInAVLTree(TreeNode* root, const tData& _val) {
		if (root == nullptr) {
			return createNewNode(_val);
		}
		if (root->val > _val) {
			root->left = InsertInAVLTree(root->left, _val);
		}
		else if (root->val < _val) {
			root->right = InsertInAVLTree(root->right, _val);
		}

		root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
		int bf = getBalanceFactor(root);

		/*Left - Left Rotation case*/
		if (bf > 1 && root->left->val > _val) {
			return rightRotate(root);
		}
		/*Right - Right Rotation case*/
		if (bf < -1 && root->right->val < _val) {
			return leftRotate(root);
		}

		/*Left - Right Rotation case*/
		if (bf > 1 && root->left->val < _val) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		/*Right - LEft Rotation case*/
		if (bf < -1 && root->right->val > _val) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		return root;
	}

	TreeNode* DeleteFromAVLTree(TreeNode* root, const tData& _val) {

		if (root == nullptr) {
			return root;
		}

		if (root->val > _val) {
			root->left = DeleteFromAVLTree(root->left, _val);
		}
		else if (root->val < _val) {
			root->right = DeleteFromAVLTree(root->right, _val);
		}
		else { //Found node to delete
			if (root->left == nullptr && root->right == nullptr) {
				delete root;
				root = nullptr;
			}
			else if (root->right == nullptr) {
				TreeNode* temp = root;
				root = root->left;
				delete temp;
			}
			else if (root->left == nullptr) {
				TreeNode* temp = root;
				root = root->right;
				delete temp;
			}
			else {
				TreeNode* temp = getMinNode(root->right);
				root->val = temp->val;
				root->right = DeleteFromAVLTree(root->right, temp->val);
			}
		}

		if (root == nullptr) {
			return root;
		}

		root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
		int balanceFactor = getBalanceFactor(root);

		if (balanceFactor > 1 && getBalanceFactor(root->left) >= 0) {
			return rightRotate(root);
		}

		if (balanceFactor > 1 && getBalanceFactor(root->left) < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		if (balanceFactor < -1 && getBalanceFactor(root->right) <= 0) {
			return leftRotate(root);
		}

		if (balanceFactor < -1 && getBalanceFactor(root->right) > 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		return root;

	}

	void preorderTraversal(TreeNode* root) {
		if (root == nullptr) {
			return;
		}
		std::cout << root->val << ":" << root->height << ":" << getBalanceFactor(root) << "\n";
		preorderTraversal(root->left);
		preorderTraversal(root->right);
	}

public:
	void Insert(const tData& val) {
		root = InsertInAVLTree(root, val);
	}

	void Delete(const tData& val) {
		root = DeleteFromAVLTree(root, val);
	}

	void preOrder() {
		preorderTraversal(root);
	}

};

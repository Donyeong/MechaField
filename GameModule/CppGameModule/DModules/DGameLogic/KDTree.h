#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
    float x, y;

    Point(float x, float y) : x(x), y(y) {}
};

struct TreeNode {
    Point point;
    TreeNode* left, * right;

    TreeNode(Point p) : point(p), left(nullptr), right(nullptr) {}
};

class KDTree {
public:
    KDTree() { root = nullptr; }
    KDTree(std::vector<Point>& points) {
        root = build(points, 0, points.size(), 0);
    }

    TreeNode* getRoot() {
        return root;
    }

    void insert(Point& p) {
        root = insert(root, p, 0);
    }

    void remove(const Point& p) {
        root = remove(root, p, 0);
    }

    static void printKDTree(TreeNode* node, int depth = 0) {
        if (node == nullptr) return;

        for (int i = 0; i < depth; ++i) std::cout << "  ";
        std::cout << "(" << node->point.x << ", " << node->point.y << ")" << std::endl;
        printKDTree(node->left, depth + 1);
        printKDTree(node->right, depth + 1);
    }

private:
    TreeNode* build(std::vector<Point>& points, int start, int end, int depth) {
        if (start >= end) return nullptr;

        int axis = depth % 2;
        auto compare = [axis](const Point& a, const Point& b) {
            return axis == 0 ? a.x < b.x : a.y < b.y;
        };

        int mid = (start + end) / 2;
        std::nth_element(points.begin() + start, points.begin() + mid, points.begin() + end, compare);

        TreeNode* node = new TreeNode(points[mid]);
        node->left = build(points, start, mid, depth + 1);
        node->right = build(points, mid + 1, end, depth + 1);
        return node;
    }
    TreeNode* insert(TreeNode* node, const Point& p, int depth) {
        if (!node) {
            return new TreeNode(p);
        }

        int axis = depth % 2;

        if ((axis == 0 && p.x < node->point.x) || (axis == 1 && p.y < node->point.y)) {
            node->left = insert(node->left, p, depth + 1);
        }
        else {
            node->right = insert(node->right, p, depth + 1);
        }

        return node;
    }

    TreeNode* remove(TreeNode* node, const Point& p, int depth) {
        if (!node) return nullptr;

        int axis = depth % 2;
        if (node->point.x == p.x && node->point.y == p.y) {  // 노드 발견
            if (node->right) {
                // 오른쪽 서브트리에서 후속 노드 찾기
                TreeNode* minNode = findMin(node->right, axis, depth + 1);
                node->point = minNode->point;
                node->right = remove(node->right, minNode->point, depth + 1);
            }
            else if (node->left) {
                TreeNode* minNode = findMin(node->left, axis, depth + 1);
                node->point = minNode->point;
                node->right = remove(node->left, minNode->point, depth + 1);
                node->left = nullptr;
            }
            else {
                delete node;
                return nullptr;
            }
        }
        else if ((axis == 0 && p.x < node->point.x) || (axis == 1 && p.y < node->point.y)) {
            node->left = remove(node->left, p, depth + 1);
        }
        else {
            node->right = remove(node->right, p, depth + 1);
        }

        return node;
    }

    TreeNode* findMin(TreeNode* node, int axis, int depth) {
        if (!node) return nullptr;

        int currAxis = depth % 2;

        if (currAxis == axis) {
            if (!node->left) {
                return node;
            }
            return findMin(node->left, axis, depth + 1);
        }

        TreeNode* leftMin = findMin(node->left, axis, depth + 1);
        TreeNode* rightMin = findMin(node->right, axis, depth + 1);

        TreeNode* minNode = node;
        if (leftMin && (currAxis == 0 ? leftMin->point.x < node->point.x : leftMin->point.y < node->point.y)) {
            minNode = leftMin;
        }
        if (rightMin && (currAxis == 0 ? rightMin->point.x < minNode->point.x : rightMin->point.y < minNode->point.y)) {
            minNode = rightMin;
        }

        return minNode;
    }

    TreeNode* root;
};

/*
int main() {
    std::vector<Point> points = {
        Point(3, 6), Point(17, 15), Point(13, 15),
        Point(6, 12), Point(9, 1), Point(2, 7),
        Point(10, 19)
    };

    KDTree tree(points);
    printKDTree(tree.getRoot());
    return 0;
}
*/
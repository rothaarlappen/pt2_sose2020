#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>

struct Tree
{
    int id;
    Tree *leftChild;
    Tree *rightChild;
    Tree *parent;
};

Tree *newTree(int id)
{
    Tree *node = new Tree();
    node->id = id;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->parent = NULL;

    return node;
}

Tree *insertNode(Tree *node, int id)
{
    static Tree *p;
    Tree *retNode;

    if (node == NULL)
    {
        retNode = newTree(id);
        retNode->parent = p;
        return retNode;
    }
    if (id <= node->id)
    {
        p = node;
        node->leftChild = insertNode(node->leftChild, id);
    }
    else
    {
        p = node;
        node->rightChild = insertNode(node->rightChild, id);
    }
    return node;
}

Tree *newTree(std::vector<int> ids)
{
    Tree *node = newTree(ids[0]);
    for (int i = 1; i < ids.size(); ++i)
        insertNode(node, ids[i]);

    return node;
}

void depthFirstTraversal(Tree *root)
{
    // TODO: Traverse the tree depth-first

}

void breadthFirstTraversal(Tree *root)
{
    // TODO: Traverse the tree breadth-first

}

void writeSVGNode(std::ofstream &stream, int id, int x, int y)
{
    // TODO: Draw a circle at (x,y) and write the ID of the node inside of it

}

void writeSVGEdge(std::ofstream &stream, int x0, int y0, int x1, int y1)
{
    // TODO: Draw a line from (x0,y0) to (x1,y1)

}

void writeSVG(Tree *root, std::string filename)
{
    // TODO: Write a valid svg file with the given filename which shows the given tree

}

int main(int argc, char **argv)
{
    Tree *root1 = newTree({6, 2, 1, 4, 3, 5, 7, 9, 8});
    Tree *root2 = newTree({5, 9, 7, 6, 2, 1, 4, 3, 8});

    std::cout << "Tree 1:" << std::endl;
    std::cout << "breadth-first: ";
    breadthFirstTraversal(root1);
    std::cout << std::endl;

    std::cout << "depth-first:   ";
    depthFirstTraversal(root1);
    std::cout << std::endl << std::endl;

    std::cout << "Tree 2:" << std::endl;
    std::cout << "breadth-first: ";
    breadthFirstTraversal(root2);
    std::cout << std::endl;

    std::cout << "depth-first:   ";
    depthFirstTraversal(root2);
    std::cout << std::endl;

    writeSVG(root1, "tree1.svg");
    writeSVG(root2, "tree2.svg");

    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include <string>

typedef std::vector<std::pair<std::string, std::string>> tagvalues;

std::string svg_stringbuilder(std::string tagName, tagvalues values){
    std::string svg_tag = "<" + tagName + " ";
    for(auto value : values){
        svg_tag += value.first + " = " + "\"" +value.second + "\"" + " ";
    }
    svg_tag += "/>\n";
    return svg_tag;
}
std::string iTOs(int i) {return std::to_string(i);}

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
    if(root == nullptr) return;
    std::cout << root->id << " ";
    depthFirstTraversal(root->leftChild);
    depthFirstTraversal(root->rightChild);

}

void breadthFirstTraversal(Tree *root)
{
    if(root == nullptr) return;
    std::vector<Tree> queue = std::vector<Tree>();
    queue.push_back(*root);

    while(queue.size() != 0){
        Tree current_tree = queue[0];
        if(current_tree.leftChild != nullptr) queue.push_back(*current_tree.leftChild);
        if(current_tree.rightChild!= nullptr) queue.push_back(*current_tree.rightChild);
        std::cout << current_tree.id << " ";
        queue.erase(queue.begin());
    }
}

void writeSVGNode(std::ofstream &stream, int id, int x, int y)
{
    // TODO: Draw a circle at (x,y) and write the ID of the node inside of it
    tagvalues circleValues = {{"cx", iTOs(x)}, {"cy", iTOs(y)}, {"r", "40"}, {"fill", "white"}, {"stroke-width", "4"}};
    stream << svg_stringbuilder("circle", circleValues);
}

void writeSVGEdge(std::ofstream &stream, int x0, int y0, int x1, int y1)
{
    // TODO: Draw a line from (x0,y0) to (x1,y1)    
    tagvalues line_values = {{"x1", iTOs(x0)}, {"x2", iTOs(x1)}, {"y1", iTOs(y0)}, {"y2", iTOs(y0)}, {"style", "stroke:black;stroke-width:4"}};
    stream << svg_stringbuilder("line", line_values);
}

void writeSVG(Tree *root, std::string filename)
{
    std::ofstream svg_file(filename);
    
    tagvalues header_values ={{"version", "1.0"}, {"encoding", "iso-8859-1"}};
    tagvalues svgTag_values = {{"width", "2000"}, {"height", "2000"}, {"style", "background:white"}};

    svg_file << svg_stringbuilder("xml", header_values);
    svg_file << svg_stringbuilder("svg", svgTag_values);


    // some algorithm...

    svg_file << "</svg>";
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

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <deque>
#include <string>
#include <math.h>

#define HEIGHT "2000"
#define WIDTH HEIGHT

typedef std::vector<std::pair<std::string, std::string>> tagvalues;

std::string svg_stringbuilder(std::string tagName, tagvalues values, std::string content = ""){
    std::string svg_tag = "<" + tagName + " ";
    for(auto value : values){
        svg_tag += value.first + "=" + "\"" +value.second + "\"" + " ";
    }
    svg_tag += ">";
    svg_tag += content;
    if(tagName != "svg"){
        svg_tag += "</" + tagName + ">\n";
    }
    return svg_tag;
}

std::string iTOs(int i) {return std::to_string(i);}

struct Point{
    int x;
    int y;
};

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

void writeText(std::ofstream &stream, std::string text, int x, int y){
    tagvalues textValues = {{"x", iTOs(x)}, {"y", iTOs(y)}, {"font-size", "35"}};
    stream << svg_stringbuilder("text", textValues, text);
}

void writeSVGNode(std::ofstream &stream, int id, int x, int y)
{
    tagvalues circleValues = {{"cx", iTOs(x)}, {"cy", iTOs(y)}, {"r", "40"}, {"fill", "white"}, {"stroke-width", "4"}, {"stroke", "black"}};

    stream << svg_stringbuilder("circle", circleValues);
    writeText(stream, iTOs(id), x, y);    
}

void writeSVGEdge(std::ofstream &stream, int x0, int y0, int x1, int y1)
{  
    tagvalues line_values = {{"x1", iTOs(x0)}, {"x2", iTOs(x1)}, {"y1", iTOs(y0)}, {"y2", iTOs(y1)}, {"style", "stroke:black;stroke-width:4"}};
    stream << svg_stringbuilder("line", line_values);
}

void writeSVGHeader (std::ofstream &stream){
    // writes svg header into stream
    tagvalues svgTag_values = {{"width", WIDTH}, {"height", HEIGHT}, {"style", "background:white"}};

    stream << "<?xml version = \"1.0\" encoding = \"iso-8859-1\"?>\n";
    stream << svg_stringbuilder("svg", svgTag_values);
}

void writeSVG(Tree *root, std::string filename)
{
    std::ofstream svg_file(filename);
    
    writeSVGHeader(svg_file);

    std::vector<std::pair<Tree, Point>> queue = std::vector<std::pair<Tree, Point>>();
    Point root_coords = {std::stoi(WIDTH)/2 , 50};
    queue.push_back({*root, root_coords});

    int y = 50;
    while(queue.size() != 0){
        Tree current_tree = queue[0].first;
        Point current_coords = queue[0].second;

        writeSVGNode(svg_file, queue[0].first.id, queue[0].second.x, queue[0].second.y);
        
        int tiefe = y / 200;        
        y = current_coords.y + 200;
        int abschnitts_groesse = std::stoi(WIDTH) / pow(2, tiefe+1);
        
        if(current_tree.leftChild != nullptr){ 
            int x = current_coords.x - (abschnitts_groesse/2);
            Point p1 = {x, y};
            queue.push_back({*current_tree.leftChild, p1});
            writeSVGEdge(svg_file, current_coords.x, current_coords.y +40, p1.x, p1.y - 40);
        }
        if(current_tree.rightChild!= nullptr){ 
            int x = current_coords.x + (abschnitts_groesse/2);
            Point p1 = {x, y};
            queue.push_back({*current_tree.rightChild, p1});
            writeSVGEdge(svg_file, current_coords.x, current_coords.y +40, p1.x, p1.y - 40);
        }
        queue.erase(queue.begin());
    }
    svg_file << "</svg>";
}

void test(){
    std::ofstream svg_file("test.svg");
    writeSVGHeader(svg_file);
    writeSVGNode(svg_file, 5, 100, 100);
    writeSVGEdge(svg_file, 100, 100, 200, 100);
    svg_file << "</svg>";
}

int main(int argc, char **argv)
{
    test();

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

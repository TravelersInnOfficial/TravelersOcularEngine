#include <iostream>
#include "TNode.h"
#include "Entities/TEntity.h"
#include "Entities/TTransform.h"
#include "Entities/TMesh.h"

int main() {

	// MAIN MENU
	TTransform* aux = new TTransform();
	TNode* parent = new TNode((TEntity*)aux);
	std::cout<<"Creando PARENT: "<< parent << "\n";
	
	aux = new TTransform();
	aux->Rotate(0, 1, 0, 90);
	TNode* node1 = new TNode(parent, (TEntity*)aux);
	std::cout<<"Creando NODE1: "<< node1 << "\n";

	aux = new TTransform();
	aux->Translate(10, 0, 0);
	TNode* node2 = new TNode(parent, (TEntity*)aux);
	std::cout<<"Creando NODE2: "<< node2 << "\n";

	aux = new TTransform();
	aux->Translate(15, 0, 0);
	TNode* node3 = new TNode(node1, (TEntity*)aux);
	std::cout<<"Creando NODE3: "<< node3 << "\n";

	aux = new TTransform();
	aux->Translate(0, 0, -10);
	TNode* node4 = new TNode(node1, (TEntity*)aux);
	std::cout<<"Creando NODE4: "<< node4 << "\n";

	TMesh* mesh = new TMesh();
	aux->Translate(0, 0, -10);
	TNode* mesh1 = new TNode(node3, (TEntity*)aux);
	std::cout<<"Creando mesh1: "<< mesh1 << "\n";

	parent->Draw();

	std::cout<<"BORRANDO PARENT: "<< parent << "\n";
	delete parent;

	return 0;
}
#include <iostream>
#include "TNode.h"
#include "Entities/TEntity.h"
#include "Entities/TTransform.h"
#include "Entities/TMesh.h"

int main() {
	std::cout<<"############################################################\n";	

	// MAIN MENU
	TTransform* aux = new TTransform();
	TNode* parent = new TNode(aux);
	std::cout<<"PARENT: "<< parent << " CREADO\n";
	aux->PrintMatrix();

	aux = new TTransform();
	aux->Rotate(0, 1, 0, 90);
	TNode* node1 = new TNode(parent, aux);
	std::cout<<"NODE1 : "<< node1 << " CREADO | Hijo de PARENT: " << node1->GetParent() << "\n";
	aux->PrintMatrix();

	aux = new TTransform();
	aux->Translate(10, 0, 0);
	TNode* node2 = new TNode(parent, aux);
	std::cout<<"NODE2 : "<< node2 << " CREADO | Hijo de PARENT: " << node2->GetParent() << "\n";
	aux->PrintMatrix();

	aux = new TTransform();
	aux->Translate(15, 0, 0);
	TNode* node3 = new TNode(node1, aux);
	std::cout<<"NODE3 : "<< node3 << " CREADO | Hijo de  NODE1: " << node3->GetParent() << "\n";
	aux->PrintMatrix();

	aux = new TTransform();
	aux->Translate(0, 0, -10);
	TNode* node4 = new TNode(node1, aux);
	std::cout<<"NODE4 : "<< node4 << " CREADO | Hijo de  NODE1: " << node4->GetParent() << "\n";
	aux->PrintMatrix();

	TMesh* mesh = new TMesh();
	TNode* mesh1 = new TNode(node3, mesh);
	std::cout<<"mesh1 : "<< mesh1 << " CREADO | Hijo de  NODE3: " << mesh1->GetParent() << "\n";

	std::cout<<"############################################################\n";		
	parent->Draw();

	std::cout<<"############################################################\n";	
	std::cout<<"\nBORRANDO PARENT: "<< parent << "\n";
	delete parent;
	
	return 0;
}
[1mdiff --git a/src/TOcularEngine/Elements/TFNode.cpp b/src/TOcularEngine/Elements/TFNode.cpp[m
[1mindex 26770ac..fb923b5 100644[m
[1m--- a/src/TOcularEngine/Elements/TFNode.cpp[m
[1m+++ b/src/TOcularEngine/Elements/TFNode.cpp[m
[36m@@ -95,7 +95,7 @@[m [mtoe::core::TOEvector3df TFNode::GetScale(){[m
 	return toRet;[m
 }[m
 [m
[31m-void TFNode::AddChild(TFNode* children){[m
[32m+[m[32mbool TFNode::AddChild(TFNode* children){[m
 	bool exists = false;[m
 	[m
 	for(int i = 0; i < m_children.size() && !exists ; i++){[m
[36m@@ -106,9 +106,10 @@[m [mvoid TFNode::AddChild(TFNode* children){[m
 		m_children.push_back(children);[m
 		children->SetParent(this);[m
 	}[m
[32m+[m	[32mreturn exists;[m
 }[m
 [m
[31m-void TFNode::RemoveChild(TFNode* children){[m
[32m+[m[32mbool TFNode::RemoveChild(TFNode* children){[m
 	bool exists = false;[m
 [m
 	for(int i = 0; i < m_children.size() && !exists; i++){[m
[36m@@ -118,6 +119,7 @@[m [mvoid TFNode::RemoveChild(TFNode* children){[m
 			exists = true;[m
 		}[m
 	}[m
[32m+[m	[32mreturn exists;[m
 }[m
 [m
 void TFNode::RemoveAllChildren(){[m
[1mdiff --git a/src/TOcularEngine/Elements/TFNode.h b/src/TOcularEngine/Elements/TFNode.h[m
[1mindex ac84ddd..7df0c45 100644[m
[1m--- a/src/TOcularEngine/Elements/TFNode.h[m
[1m+++ b/src/TOcularEngine/Elements/TFNode.h[m
[36m@@ -28,8 +28,8 @@[m [mpublic:[m
 	virtual toe::core::TOEvector3df GetRotation();		// Returns the position of the Node[m
 	virtual toe::core::TOEvector3df GetScale();			// Returns the scale of the Node[m
 [m
[31m-	void AddChild(TFNode* children);	// Adds a Children to the TFNode[m
[31m-	void RemoveChild(TFNode* children);			// Removes Children from the TFNode[m
[32m+[m	[32mbool AddChild(TFNode* children);	// Adds a Children to the TFNode[m
[32m+[m	[32mbool RemoveChild(TFNode* children);			// Removes Children from the TFNode[m
 	void RemoveAllChildren();					// Remove ALL Children from the TFNode[m
 [m
 	void SetParent(TFNode* parent = nullptr);	// Adds a Parent to the TFNode[m
[1mdiff --git a/src/TOcularEngine/Elements/TFRoom.h b/src/TOcularEngine/Elements/TFRoom.h[m
[1mindex 4e2b042..e2b20df 100644[m
[1m--- a/src/TOcularEngine/Elements/TFRoom.h[m
[1m+++ b/src/TOcularEngine/Elements/TFRoom.h[m
[36m@@ -24,9 +24,9 @@[m [mpublic:[m
 	toe::core::TOEvector3df GetScale() override;[m
 [m
 	float GetDistance(toe::core::TOEvector3df position);[m
[31m-	TNode* GetConnectionNode() override;[m
 [m
 private:[m
[32m+[m	[32mTNode* GetConnectionNode() override;[m
 	TFRoom(toe::core::TOEvector3df position = toe::core::TOEvector3df(0, 0, 0),[m
 		toe::core::TOEvector3df rotation = toe::core::TOEvector3df(0, 0, 0),[m
 		toe::core::TOEvector3df scale = toe::core::TOEvector3df(1, 1, 1));[m
[1mdiff --git a/src/TOcularEngine/SceneManager.cpp b/src/TOcularEngine/SceneManager.cpp[m
[1mindex fd63bd3..d92c9c9 100644[m
[1m--- a/src/TOcularEngine/SceneManager.cpp[m
[1m+++ b/src/TOcularEngine/SceneManager.cpp[m
[36m@@ -181,6 +181,20 @@[m [mbool SceneManager::DeleteMesh(TFNode* node){[m
 	return toRet;[m
 }[m
 [m
[32m+[m[32mbool SceneManager::DeleteRoom(TFNode* node){[m
[32m+[m	[32mbool toRet = false;[m
[32m+[m
[32m+[m	[32mstd::vector<TFRoom*>::iterator it = m_rooms.begin();[m
[32m+[m	[32mfor(; it != m_rooms.end() && !toRet; ++it){[m
[32m+[m		[32mif(*it == node){[m
[32m+[m			[32mm_rooms.erase(it);[m
[32m+[m			[32mdelete node;[m
[32m+[m			[32mtoRet = true;[m
[32m+[m		[32m}[m
[32m+[m	[32m}[m
[32m+[m	[32mreturn toRet;[m
[32m+[m[32m}[m
[32m+[m
 void SceneManager::SetAmbientLight(toe::core::TOEvector3df ambientLight){[m
 	m_ambientLight = glm::vec3(ambientLight.X, ambientLight.Y, ambientLight.Z);[m
 }[m
[1mdiff --git a/src/TOcularEngine/SceneManager.h b/src/TOcularEngine/SceneManager.h[m
[1mindex cfd8106..68b2ac5 100644[m
[1m--- a/src/TOcularEngine/SceneManager.h[m
[1m+++ b/src/TOcularEngine/SceneManager.h[m
[36m@@ -146,6 +146,14 @@[m [mpublic:[m
      */[m
     bool DeleteMesh(TFNode*);[m
 [m
[32m+[m[32m    /**[m
[32m+[m[32m     * @brief      Delete the Room given[m
[32m+[m[32m     *[m
[32m+[m[32m     * @return     true The mesh has been deleted[m
[32m+[m[32m     * @return     false The mesh couldn't be deleted[m
[32m+[m[32m     */[m
[32m+[m[32m    bool DeleteRoom(TFNode*);[m
[32m+[m
     /**[m
      * @brief Sets the Ambient Light[m
      * [m

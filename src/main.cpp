#include "TOcularEngine/TOcularEngine.h"

int main(){
	VideoDriver* VDriv = toe::GetVideoDriver();
	VDriv->CreateWindow("Wizards&Warlocks",toe::core::vector2df(800,600));

	VDriv->SetClearScreenColor(toe::core::vector4df(0.7, 0.7, 1, 1));
	while(VDriv->Update()) VDriv->Draw();

    return EXIT_SUCCESS;
}
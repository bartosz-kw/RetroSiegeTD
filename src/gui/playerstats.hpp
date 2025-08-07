#include "../structs/textlabel.hpp"

class GuiManager;
class PlayerStats
{
private:
    GuiManager* mgr_gui = nullptr;
private:
    void InitLabels();
    
public:
    void InjectDependencies(GuiManager* guiManager);
    void Init();
};

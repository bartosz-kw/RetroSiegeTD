#pragma once
class GuiManager;

class MainMenu
{
private:

    GuiManager* mgr_gui = nullptr;

private:
    void InitLabels();
    void InitButtons();

public:
    void InjectDependencies(GuiManager* guiManager);
    void Init();
};

#pragma once

class GuiManager;
class Game;

class MainMenu
{
private:
    Game *mgr_game = nullptr;
    GuiManager *mgr_gui = nullptr;

private:
    void InitLabels();
    void InitButtons();

public:
    void InjectDependencies(GuiManager *guiManager, Game *game);
    void Init();
};

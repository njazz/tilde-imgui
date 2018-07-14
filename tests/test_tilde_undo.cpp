#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "UndoStack.hpp"
#include "json.hpp"

TEST_CASE("undo: basic", "[tilde~ PureData IDE]")
{
    SECTION("actions")
    {
        UndoStack undoStack;

        int actionValue = -1;

        auto action_Do = [&]() {
            actionValue = 10;
        };
        auto action_Undo = [&]() {
            actionValue = 0;
        };

        REQUIRE(!undoStack.canUndo());
        REQUIRE(!undoStack.canRedo());

        undoStack.doAction(UICommand::makePtr("action", action_Do, action_Undo));

        REQUIRE(actionValue == 10);

        REQUIRE(!undoStack.canRedo());

        undoStack.undoLastAction();

        REQUIRE(actionValue == 0);

        // redo
        REQUIRE(undoStack.canRedo());
        undoStack.redoLastAction();

        REQUIRE(actionValue == 10);
        REQUIRE(undoStack.canUndo());
        REQUIRE(!undoStack.canRedo());
    }

    SECTION("action list")
    {
        UndoStack undoStack;

        REQUIRE(undoStack.undoActionCount() == 0);

        undoStack.doAction(UICommand::makePtr("action-1", []() {}, []() {}));
        undoStack.doAction(UICommand::makePtr("action-2", []() {}, []() {}));
        undoStack.doAction(UICommand::makePtr("action-3", []() {}, []() {}));

        REQUIRE(undoStack.undoActionCount() == 3);
        REQUIRE(undoStack.undoActionsList().at(0) == "action-1");
        REQUIRE(undoStack.undoActionsList().at(1) == "action-2");
        REQUIRE(undoStack.undoActionsList().at(2) == "action-3");

        REQUIRE (undoStack.undoActionName() == "action-3");
        REQUIRE (undoStack.redoActionName() == "");

        undoStack.undoLastAction();
        undoStack.undoLastAction();

        REQUIRE(undoStack.undoActionCount() == 1);
        REQUIRE(undoStack.undoActionsList().at(0) == "action-1");

        REQUIRE (undoStack.undoActionName() == "action-1");
        REQUIRE (undoStack.redoActionName() == "action-2");
    }
}

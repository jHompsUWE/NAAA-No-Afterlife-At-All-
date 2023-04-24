#pragma once
#include "PlaneType.h"

enum class EventType
{
    // InputEvents
    PAUSE,
    LOAD_GAME,
    LOAD_SCENARIO,
    SAVE_GAME,
    QUIT,
    AUDIO_MENU,
    NEW_GAME,
    CLOSE,
    PORTS,
    TOPIAS,
    GRAPHVIEW,
    ACTIVATE_MISC_ZONING,
    TOGGLE_MAPVIEW,
    GATES,
    TOGGLE_HELPERS,
    SOUL_VIEW,
    ACTIVATES_KARMA_STATION_ZONING,
    ACTIVATES_LIMBO_ZONING,
    MICROVIEW,
    TRAINING_CENTRE,
    ACTIVATES_OMNIBULGE_LOVEDOME_ZONNIG,
    TOGGLE_PLANET_VIEW,
    ROADS,
    SPECIAL_BUILDINGS,
    KARMA_TRACK,
    TOGGLE_MACROMANAGER,
    NUKE_BUTTON,
    TOGGLE_REMOTE_CONTROL,
    TOGGLE_PREVIOUS_TEMPO_AND_DEVINE_INTERVENTION,
    ZOOM_IN,
    ZOOM_OUT,
    SNAP_TO_HEAVEN,
    SNAP_TO_HELL,
    SCROLL_UP,
    SCROLL_RIGHT,
    SCROLL_LEFT,
    SCROLL_DOWN,
    ROTATE_REALMS_RIGHT,
    ROTATE_REALMS_LEFT,
    GREEN_ZONING,
    YELLOW_ZONING,
    ORANGE_ZONING,
    BROWN_ZONING,
    PURPLE_ZONING,
    RED_ZONING,
    BLUE_ZONING,
    GENERIC_ZONING,

    // UI Remote specific events
    SIPHONS_BANKS,
    ROTATE_REALMS_UP,
    ROTATE_REALMS_DOWN,
    FLATTEN_HELL,
    FLATTEN_HEAVEN,
    FLATTEN_KARMA,
    FLATTEN_GRID,

    // GameEvents
    STATE_TRANSITION,
    SOUL_UPDATE,
    ADD_SOUL
};

class Event
{
public:
    struct StateTransition
    {
        int previous;
        int current;
    };

    struct SoulUpdate
    {
        int count;
    };

    struct AddSoul
    {
        PlaneType plane = PlaneType::None;
        int x;
        int y;
    };

	union EventPayload
	{
        StateTransition state_transition;
        SoulUpdate soul_update;
        AddSoul add_soul;
	};

	////////////////////////////////////////////////////////////
	/// \brief Holds the event-specific data.
	////////////////////////////////////////////////////////////
	EventPayload payload;

	////////////////////////////////////////////////////////////
	/// \brief Helps users avoid undefined behaviour. Check the type and only read from the corresponding payload member. 
	////////////////////////////////////////////////////////////
	EventType type;

	////////////////////////////////////////////////////////////
	/// \brief The time between the update cycle in which the event is trigger and the update cycle in which it is executed in seconds, defaulted to 0 for an immediate event. 
	////////////////////////////////////////////////////////////
	float delay = 0;
};

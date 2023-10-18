#pragma once

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#define MAX_BULLET 100
#define MAX_ITEM 4
//#define MAX_OBJECTS 100
//#define MAX_BULLET 30
#define HERO_ID 0

#define GRAVITY 9.8f

#define UPDATE_RATE 30

/* typedef */
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

using UserID = int32;

#define MAX_BUFFER_SIZE 2000
#define UPDATE_FREQUENCY 0.006

enum class ObjectType : uint8 {
	TYPE_NORMAL = 0,
	TYPE_BULLET = 1,
};

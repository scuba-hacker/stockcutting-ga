#ifndef _define_vars_h
#define _define_vars_h

typedef unsigned long x_size_t;
typedef unsigned long y_size_t;
typedef unsigned long xy_size_t;
typedef signed int x_pos_t;
typedef signed int y_pos_t;
typedef signed int pos_t;

typedef double fitness_score;


typedef unsigned long array_index;
typedef unsigned long sequence_size;



enum angle {_0_degrees, _90_degrees};
enum status {SUCCESS, FAILURE};
enum compare { SMALLER, EQUAL, LARGER };
enum orderproperty { ASCENDING, DESCENDING };
enum ordering { DATA, COUNTER };
enum placement_rule { LEFTMOST, ILEFTMOST, TOPMOST, ITOPMOST, FLIP_LEFT, FLIP_TOP, DYNAMIC};
enum profile_t { MODIFY_LEFT_PROFILE, MODIFY_TOP_PROFILE };
enum update_t { u_CURRENT, u_RANDOM, u_ORDER };
enum sheetflag_t { s_NO, s_YES, s_FAILED };
enum copy_t { c_FIRST, c_SECOND, c_ALL };






#endif


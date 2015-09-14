#ifndef REFERENCE_FRAMES_H
#define REFERENCE_FRAMES_H

#include <string>
#include "worldmap.h"
#include "string_grammar.h"
#include "homotopic_grammar.h"

static std::string CENTER_POINT_ID_CHARACTER = "C";

typedef enum {
    STRING_GRAMMAR_TYPE,
    HOMOTOPIC_GRAMMAR_TYPE
} grammar_type_t;

class ReferenceFrame {
public:
  ReferenceFrame();
  virtual ~ReferenceFrame();
 
  std::string m_name; 
  Segment2D   m_segment;
  bool        m_connect_to_cp;
};

class ReferenceFrameSet {

public:
    ReferenceFrameSet();
    virtual ~ReferenceFrameSet();

    void init(int width, int height, std::vector< std::vector<Point2D> >& obstacles);
    StringGrammar* get_string_grammar( Point2D init, Point2D goal );
    HomotopicGrammar* get_homotopic_grammar( Point2D init, Point2D goal );

    std::vector< std::string > get_string ( Point2D start, Point2D end, grammar_type_t type );
    std::vector< std::string > get_string ( std::vector<Point2D> points, grammar_type_t type );
    std::vector<ReferenceFrame*>& get_reference_frames() { return _reference_frames; }

    WorldMap* get_world_map() { return _p_world_map; }

protected:
    StringGrammar* get_string_grammar( SubRegion* p_init, SubRegion* p_goal );
    HomotopicGrammar* get_homotopic_grammar( SubRegion* p_init, SubRegion* p_goal );

private:
    WorldMap*                    _p_world_map;
    std::vector<ReferenceFrame*> _reference_frames;
};

#endif // REFERENCE_FRAMES_H

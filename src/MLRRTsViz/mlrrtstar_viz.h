#ifndef MLRRTSTAR_VIZ_H_
#define MLRRTSTAR_VIZ_H_

#include <QLabel>

#include "mlrrtstar.h"
#include "mlrrtstar_path_planning_info.h"
#include "reference_frames.h"

namespace mlrrts{

  enum MLRRTstarVizMode{
    NORMAL,
    DRAWING
  };

  class MLRRTstarViz : public QLabel
  {
    Q_OBJECT
  public:
    explicit MLRRTstarViz(QWidget* parent = 0);
    void set_tree(MLRRTstar* p_tree);
    void set_reference_frame_set(homotopy::ReferenceFrameSet* p_rf);
    bool draw_path(QString filename);
    bool save_current_viz(QString filename);

    void set_show_reference_frames( bool show );
    void set_show_regions( bool show );
    void set_finished_planning( bool finished ) { m_finished_planning = finished; }
    bool get_finished_planning() { return m_finished_planning; }

    bool show_reference_frames() { return m_show_reference_frames; }
    bool show_regions() { return m_show_regions; }
    bool is_finished_planning() { return m_finished_planning; }
 
    homotopy::ReferenceFrame* get_selected_reference_frame();
    homotopy::SubRegion*      get_selected_subregion();

    void prev_subregion();
    void next_subregion();

    void prev_string_class();
    void next_string_class();
    int get_string_class_index() { return m_string_class_index; }
    QString get_string_class_info();

    void prev_reference_frame();
    void next_reference_frame();
    void prev_found_path();
    void next_found_path();
    int  get_reference_frame_index() { return m_reference_frame_index; }
    std::string get_reference_frame_name();
    std::string get_subregion_name();

    QString generate_string();
    void import_string_constraint( std::vector< QPoint > points, homotopy::grammar_type_t type );

    MLRRTstarPathPlanningInfo m_PPInfo;

    std::vector<QPoint>& get_drawed_points() { return m_drawed_points; }
    void set_show_drawed_points( bool show ) { m_show_points = show; }
    bool get_show_drawed_points() { return m_show_points; }
    
    int get_found_path_index() { return m_found_path_index; }
    QString item_selected( QPoint pos ); 
  signals:
  
  public slots:

  protected:
    void mousePressEvent( QMouseEvent * event );
    void mouseMoveEvent( QMouseEvent * event );
    void mouseReleaseEvent( QMouseEvent * event );

    std::vector<QPoint>  m_drawed_points;
    bool                 m_dragging;
    bool                 m_show_points;
    MLRRTstarVizMode     m_mode;
    QString              m_item_selected_name;
  private:
    void draw_path_on_map(QPixmap& map);
    void draw_current_viz(QPixmap& map);
    void paint(QPaintDevice * device);

    MLRRTstar*                   mp_tree;
    homotopy::ReferenceFrameSet* mp_reference_frames;
    bool                         m_show_reference_frames;
    bool                         m_show_regions;
    bool                         m_finished_planning;
    int                          m_string_class_index;
    int                          m_reference_frame_index;
    int                          m_found_path_index;
    int                          m_subregion_index;

    std::vector<SubRegion*>      m_viz_subregions;
    std::vector<ReferenceFrame*> m_viz_reference_frames;
 
  private slots:
    void paintEvent( QPaintEvent* e );
  };
}

#endif /* MLRRTSTAR_VIZ_H_ */

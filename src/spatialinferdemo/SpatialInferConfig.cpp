#include <QVBoxLayout>
#include <QHBoxLayout>
#include "SpatialInferWindow.hpp"
#include "SpatialInferConfig.hpp"

using namespace std;

namespace topologyPathPlanning {

namespace topologyinference {

SpatialInferConfig::SpatialInferConfig( SpatialInferWindow* parent ) {
  mpParentWindow = parent;

  mpLabelSpatialRelations = new QLabel("Spatial Relation Functions");
  
  mpListWidget = new QListWidget();
  mpListWidget->setViewMode(QListView::IconMode);
  mpListWidget->show();

  mpBtnRemove = new QPushButton(tr("Remove"));
  mpBtnOK = new QPushButton(tr("OK"));
  QHBoxLayout* buttonsLayout = new QHBoxLayout();
  buttonsLayout->addWidget( mpBtnRemove );
  buttonsLayout->addWidget( mpBtnOK );
  
  connect(mpBtnRemove, SIGNAL(clicked()), this, SLOT(onBtnRemoveClicked()) );
  connect(mpBtnOK, SIGNAL(clicked()), this, SLOT(onBtnOKClicked()) );

  QVBoxLayout* mainLayout = new QVBoxLayout();
  mainLayout->addWidget( mpLabelSpatialRelations );
  mainLayout->addWidget( mpListWidget );
  mainLayout->addLayout( buttonsLayout );

  setLayout( mainLayout );
}

void SpatialInferConfig::onBtnOKClicked() {
  close();
}
 
void SpatialInferConfig::onBtnRemoveClicked() {
  QList<QListWidgetItem*> selected_items = mpListWidget->selectedItems();
  QList<QListWidgetItem*>::const_iterator iter;
  for( iter = selected_items.begin(); iter != selected_items.end(); iter++ ) {
    QListWidgetItem* p_item = (*iter);
    if( p_item ) {
      if( mpParentWindow ) {
        if( mpParentWindow->mpViz ) {
          mpParentWindow->mpViz->getSpatialRelationMgr()->removeSpatialRelationFunction( p_item->text().toStdString() );
        }
      }
    } 
  }
  qDeleteAll( selected_items );
}

void SpatialInferConfig::updateDisplay() {
  mpListWidget->clear();
  if( mpParentWindow ) {
    if( mpParentWindow->mpViz ) {
      vector< string > names = mpParentWindow->mpViz->getSpatialRelationMgr()->getSpatialRelationFunctionNames();
      for( unsigned int i = 0; i < names.size(); i++ ) {
        mpListWidget->addItem( QString::fromStdString( names[i] ) );
      }
    }
  }
  repaint();
}


} // topologyinference

} // topologyPathPlanning

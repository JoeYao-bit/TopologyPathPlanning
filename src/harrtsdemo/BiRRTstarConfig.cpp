#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include "BiRRTstarConfig.hpp"
#include "BiRRTstarWindow.hpp"

#define STRING_GRAMMAR_STR    "String grammar"
#define HOMOTOPIC_GRAMMAR_STR "Homotopic grammar"
#define START_TREE_RUN_STR    "Run start tree"
#define GOAL_TREE_RUN_STR     "Run goal tree"
#define BOTH_TREES_RUN_STR    "Run both trees"

using namespace topologyPathPlanning::homotopy;

namespace topologyPathPlanning {

namespace harrts{


BIRRTstarConfig::BIRRTstarConfig(BIRRTstarWindow * parent) {
  mpParentWindow = parent;

  mpCheckMinDist = new QCheckBox();
  if (mpParentWindow->mpViz->m_PPInfo.mMinDistEnabled==true) {
    mpCheckMinDist->setChecked(true);
  }
  else {
    mpCheckMinDist->setChecked(false);
  }
  connect(mpCheckMinDist , SIGNAL(stateChanged(int)),this, SLOT(checkBoxStateChanged(int)));
  mpLabelMinDist = new QLabel("Minimize distance");

  mpLabelIterationNum = new QLabel("Iteration Num: ");
  mpLineEditIterationNum = new QLineEdit();
  mpLineEditIterationNum->setText(QString::number(mpParentWindow->mpViz->m_PPInfo.mMaxIterationNum));
  mpLineEditIterationNum->setMaximumWidth(40);
  mpLabelSegmentLength = new QLabel("Segment Len: ");
  mpLineEditSegmentLength = new QLineEdit();
  mpLineEditSegmentLength->setText(QString::number(mpParentWindow->mpViz->m_PPInfo.mSegmentLength));
  mpLineEditSegmentLength->setMaximumWidth(40);

  mpLabelCost = new QLabel("Cost Map: ");
  mpLineEditCost = new QLineEdit();
  mpLineEditCost->setText(mpParentWindow->mpViz->m_PPInfo.mObjectiveFile);
  mpLineEditCost->setMaximumWidth(300);

  QHBoxLayout * minDistLayout = new QHBoxLayout();
  minDistLayout->addWidget(mpCheckMinDist);
  minDistLayout->addWidget(mpLabelMinDist);
  minDistLayout->addWidget(mpLabelIterationNum);
  minDistLayout->addWidget(mpLineEditIterationNum);
  minDistLayout->addWidget(mpLabelSegmentLength);
  minDistLayout->addWidget(mpLineEditSegmentLength);
  mpBtnAdd = new QPushButton(tr("Add"));
  connect(mpBtnAdd, SIGNAL(clicked()), this, SLOT(onBtnAddClicked()));

  QHBoxLayout * costMapLayout = new QHBoxLayout();
  costMapLayout->addWidget(mpLabelCost);
  costMapLayout->addWidget(mpLineEditCost);
  costMapLayout->addWidget(mpBtnAdd);
   
  QHBoxLayout * typeLayout = new QHBoxLayout();
  mpLabelGrammarType = new QLabel("Grammar type:");
  mpComboGrammarType = new QComboBox();
  mpComboGrammarType->addItem(STRING_GRAMMAR_STR);
  mpComboGrammarType->addItem(HOMOTOPIC_GRAMMAR_STR);
  mpComboGrammarType->setCurrentIndex(static_cast<int>( mpParentWindow->mpViz->m_PPInfo.mGrammarType));
  mpLabelRunType = new QLabel("Run type:");
  mpComboRunType = new QComboBox();
  mpComboRunType->addItem(START_TREE_RUN_STR);
  mpComboRunType->addItem(GOAL_TREE_RUN_STR);
  mpComboRunType->addItem(BOTH_TREES_RUN_STR);
  mpComboRunType->setCurrentIndex(static_cast<int>( mpParentWindow->mpViz->m_PPInfo.mRunType));
  typeLayout->addWidget(mpLabelGrammarType);
  typeLayout->addWidget(mpComboGrammarType);
  typeLayout->addWidget(mpLabelRunType);
  typeLayout->addWidget(mpComboRunType); 

  mpBtnOK = new QPushButton(tr("OK"));
  mpBtnCancel = new QPushButton(tr("Cancel"));
  connect(mpBtnOK, SIGNAL(clicked()), this, SLOT(onBtnOKClicked()));
  connect(mpBtnCancel, SIGNAL(clicked()), this, SLOT(onBtnCancelClicked()));

  QHBoxLayout * buttonsLayout = new QHBoxLayout();
  buttonsLayout->addWidget(mpBtnOK);
  buttonsLayout->addWidget(mpBtnCancel);

  QVBoxLayout * mainLayout = new QVBoxLayout();
  mainLayout->addLayout(minDistLayout);
  mainLayout->addLayout(costMapLayout);
  mainLayout->addLayout(typeLayout);
  mainLayout->addLayout(buttonsLayout);

  setWindowTitle("Config Objectives");

  setLayout(mainLayout);
}

void BIRRTstarConfig::onBtnOKClicked() {
  updateConfiguration();
  close();
}

void BIRRTstarConfig::onBtnCancelClicked() {
  close();
}

void BIRRTstarConfig::onBtnAddClicked() {
  QString objFilename = QFileDialog::getOpenFileName(this,
                 tr("Open Objective File"), "./", tr("Objective Files (*.*)"));
  if (objFilename!="") {
    if(true==isCompatible(objFilename)) {
      if(mpParentWindow->mpViz) {
        mpLineEditCost->setText(objFilename);
        repaint();
      }
    }
  }
  else {
    QMessageBox msg;
    msg.setText("Fitness distribution file is not compatible!");
    msg.exec();
  }
}


void BIRRTstarConfig::updateDisplay() {
  if(mpParentWindow) {
    if(mpParentWindow->mpViz) {
      if( mpParentWindow->mpViz->m_PPInfo.mMinDistEnabled==true ) {
        mpCheckMinDist->setChecked(true);
      }
      else {
        mpCheckMinDist->setChecked(false);
      }
      mpLineEditSegmentLength->setText(QString::number(mpParentWindow->mpViz->m_PPInfo.mSegmentLength));
      mpLineEditIterationNum->setText(QString::number(mpParentWindow->mpViz->m_PPInfo.mMaxIterationNum));
      mpLineEditCost->setText(mpParentWindow->mpViz->m_PPInfo.mObjectiveFile);

      mpComboGrammarType->setCurrentIndex((int)mpParentWindow->mpViz->m_PPInfo.mGrammarType);
      mpComboRunType->setCurrentIndex((int)mpParentWindow->mpViz->m_PPInfo.mRunType);
    }
  }
}

void BIRRTstarConfig::updateConfiguration() {
  int numObj = 0;
  if (mpCheckMinDist->isChecked()==true) {
    numObj += 1;
    mpParentWindow->mpViz->m_PPInfo.mMinDistEnabled=true;
  }
  else {
    mpParentWindow->mpViz->m_PPInfo.mMinDistEnabled=false;
  }

  mpParentWindow->mpViz->m_PPInfo.mObjectiveFile = mpLineEditCost->text();
  mpParentWindow->mpViz->m_PPInfo.mMaxIterationNum = mpLineEditIterationNum->text().toInt();
    mpParentWindow->mpViz->m_PPInfo.mSegmentLength = mpLineEditSegmentLength->text().toDouble();
    
  int grammar_type_idx = mpComboGrammarType->currentIndex();
  mpParentWindow->mpViz->m_PPInfo.mGrammarType = static_cast< grammar_type_t >( grammar_type_idx);
  int run_type_idx = mpComboRunType->currentIndex();
  mpParentWindow->mpViz->m_PPInfo.mRunType = static_cast< RRTree_run_type_t >( run_type_idx);

}

bool BIRRTstarConfig::isCompatible(QString fitnessFile) {
  QPixmap pixmap(fitnessFile);
  if (pixmap.width()==mpParentWindow->mpViz->m_PPInfo.mMapWidth
          && pixmap.height()==mpParentWindow->mpViz->m_PPInfo.mMapHeight) {
    return true;
  }
  return false;
}

void BIRRTstarConfig::checkBoxStateChanged(int state) {
  if(mpCheckMinDist->checkState()==Qt::Checked) {
    mpLineEditCost->setEnabled(false);
    mpBtnAdd->setEnabled(false);
  }
  else {
    mpLineEditCost->setEnabled(true);
    mpBtnAdd->setEnabled(true);
  }
  repaint();
}

} // harrts

} // topologyPathPlanning

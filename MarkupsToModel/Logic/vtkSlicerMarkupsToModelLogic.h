/*==============================================================================

Program: 3D Slicer

Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

See COPYRIGHT.txt
or http://www.slicer.org/copyright/copyright.txt for details.

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

==============================================================================*/

// .NAME vtkSlicerMarkupsToModelLogic - slicer logic class to convert markups to models
// .SECTION Description
// This class manages the logic associated with selecting, adding and removing markups and converting these markups to either a:
// a) closed surface using vtkDelaunay3D triangulation
// b) piece wise connected curve. The curve can be linear, Cardinal or Kochanek Splines


#ifndef __vtkSlicerMarkupsToModelLogic_h
#define __vtkSlicerMarkupsToModelLogic_h

// Slicer includes
#include "vtkSlicerModuleLogic.h"
#include "vtkSlicerMarkupsLogic.h"

// vtk includes
#include <vtkDoubleArray.h>
#include <vtkMatrix4x4.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>

// MRML includes
#include "vtkMRMLMarkupsToModelNode.h"

// STD includes
#include <cstdlib>

#include "vtkSlicerMarkupsToModelModuleLogicExport.h"

class vtkMRMLMarkupsFiducialNode;
class vtkMRMLMarkupsToModelNode;
class vtkMRMLModelNode;
class vtkPolyData;

/// \ingroup Slicer_QtModules_ExtensionTemplate
class VTK_SLICER_MARKUPSTOMODEL_MODULE_LOGIC_EXPORT vtkSlicerMarkupsToModelLogic :
  public vtkSlicerModuleLogic
{
public:

  static vtkSlicerMarkupsToModelLogic *New();
  vtkTypeMacro(vtkSlicerMarkupsToModelLogic, vtkSlicerModuleLogic);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Sets the markups node to be transformed
  void SetMarkupsNode( vtkMRMLMarkupsFiducialNode* newMarkups, vtkMRMLMarkupsToModelNode* moduleNode );

  vtkSlicerMarkupsLogic* MarkupsLogic;
  // Updates the mouse selection type to create markups or to navigate the scene.
  void UpdateSelectionNode( vtkMRMLMarkupsToModelNode* markupsToModelModuleNode );
  // Updates closed surface or curve output model from markups
  void UpdateOutputModel( vtkMRMLMarkupsToModelNode* moduleNode );

  void ProcessMRMLNodesEvents( vtkObject* caller, unsigned long event, void* callData );

  // Low-level interface for generating closed surface model without creating a parameter node
  bool UpdateClosedSurfaceModel(vtkMRMLMarkupsFiducialNode* markupsNode, vtkMRMLModelNode* modelNode, bool smoothing = true, bool forceConvex = false, double delaunayAlpha = 0.0, bool cleanMarkups = true);

  // Low-level interface for generating curve model without creating a parameter node
  bool UpdateOutputCurveModel(vtkMRMLMarkupsFiducialNode* markupsNode, vtkMRMLModelNode* modelNode,
    int interpolationType = vtkMRMLMarkupsToModelNode::Linear,
    bool tubeLoop = false, double tubeRadius = 1.0, int tubeNumberOfSides = 8, int tubeSegmentsBetweenControlPoints = 5,
    bool cleanMarkups = true, int polynomialOrder = 3, int pointParameterType = vtkMRMLMarkupsToModelNode::RawIndices);

protected:
  vtkSlicerMarkupsToModelLogic();
  virtual ~vtkSlicerMarkupsToModelLogic();

  virtual void SetMRMLSceneInternal(vtkMRMLScene* newScene);
  /// Register MRML Node classes to Scene. Gets called automatically when the MRMLScene is attached to this logic class.
  virtual void RegisterNodes();
  virtual void UpdateFromMRMLScene();
  ///When a scene has been imported it will set the markups list and model.
  virtual void OnMRMLSceneEndImport();
  virtual void OnMRMLSceneStartImport();
  virtual void OnMRMLSceneNodeAdded(vtkMRMLNode* node);
  virtual void OnMRMLSceneNodeRemoved(vtkMRMLNode* node);

private:
  vtkSlicerMarkupsToModelLogic(const vtkSlicerMarkupsToModelLogic&); // Not implemented
  void operator=(const vtkSlicerMarkupsToModelLogic&); // Not implemented  
};

#endif

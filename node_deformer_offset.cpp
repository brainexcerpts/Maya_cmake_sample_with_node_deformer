//-
// ==========================================================================
// Copyright 1995,2006,2008 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
// ==========================================================================
//+

//
//  File: offset.cc
//
//  Description:
//              Example implementation of a deformer. This node
//              offsets vertices according to the CV's weights.
//              The weights are set using the set editor or the
//              percent command.
//

#include <string.h>
#include <maya/MIOStream.h>
#include <math.h>

#include <maya/MPxDeformerNode.h>
#include <maya/MItGeometry.h>
#include <maya/MPxLocatorNode.h>

#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnMatrixData.h>

#include <maya/MFnPlugin.h>
#include <maya/MFnDependencyNode.h>

#include <maya/MTypeId.h>
#include <maya/MPlug.h>

#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MArrayDataHandle.h>

#include <maya/MPoint.h>
#include <maya/MVector.h>
#include <maya/MMatrix.h>

#include <maya/MDagModifier.h>

#if 0
class Offset_dfm : public MPxDeformerNode
{
public:
    Offset_dfm();
    virtual ~Offset_dfm();

    static  void*   creator();
    static  MStatus initialize();

    // deformation function
    virtual MStatus deform(MDataBlock& block,
                           MItGeometry& iter,
                           const MMatrix& mat,
                           unsigned int multiIndex);

    // when the accessory is deleted, this node will clean itself up
    virtual MObject& accessoryAttribute() const;

    // create accessory nodes when the node is created
    virtual MStatus accessoryNodeSetup(MDagModifier& cmd);

public:
    // local node attributes
    static  MObject s_offset_matrix; // offset center and axis
    static  MTypeId s_id;

private:
};

MTypeId Offset_dfm::s_id( 0x8000c );

// local attributes
//
MObject Offset_dfm::s_offset_matrix;

// ----------------------------------------------------------------------------

Offset_dfm::Offset_dfm() {}
Offset_dfm::~Offset_dfm() {}

// ----------------------------------------------------------------------------

void* Offset_dfm::creator()
{
    return new Offset_dfm();
}

// ----------------------------------------------------------------------------

MStatus Offset_dfm::initialize()
{
    // local attribute initialization

    MFnMatrixAttribute  matrix_attr;
    s_offset_matrix = matrix_attr.create( "locateMatrix", "lm");
    matrix_attr.setStorable(false);
    matrix_attr.setConnectable(true);

    //  deformation attributes
    addAttribute( s_offset_matrix);

    attributeAffects( Offset_dfm::s_offset_matrix, Offset_dfm::outputGeom );

    return MStatus::kSuccess;
}

// ----------------------------------------------------------------------------

/** @brief Deform the point with a squash algorithm
 *  @param block      : the datablock of the node
 *  @param iter       : an iterator for the geometry to be deformed
 *  @param m          : matrix to transform the point into world space
 *  @param multiIndex : the index of the geometry that we are deforming
*/
MStatus Offset_dfm::deform( MDataBlock& block,
                        MItGeometry& iter,
                        const MMatrix& /*m*/,
                        unsigned int multiIndex)
{
    MStatus status;

    // Envelope data from the base class.
    // The envelope is simply a scale factor.
    //
    MDataHandle envelope_handle = block.inputValue(envelope, &status);
    if (MS::kSuccess != status) return status;
    float env = envelope_handle.asFloat();

    // Get the matrix which is used to define the direction and scale
    // of the offset.
    //
    MDataHandle matrix_handle = block.inputValue(s_offset_matrix, &status );
    if (MS::kSuccess != status)
        return status;

    MMatrix omat = matrix_handle.asMatrix();
    MMatrix omat_inv = omat.inverse();

    // iterate through each point in the geometry
    //
    for ( ; !iter.isDone(); iter.next())
    {
        MPoint pt = iter.position();
        pt *= omat_inv;

        float weight = weightValue(block, multiIndex, iter.index());

        // offset algorithm
        //
        pt.y = pt.y + env*weight;
        //
        // end of offset algorithm

        pt *= omat;
        iter.setPosition(pt);
    }
    return status;
}

// ----------------------------------------------------------------------------

/* override */
//
//      Description:
//        This method returns a the attribute to which an accessory
//    shape is connected. If the accessory shape is deleted, the deformer
//        node will automatically be deleted.
//
//    This method is optional.
//
MObject& Offset_dfm::accessoryAttribute() const
{
    return Offset_dfm::s_offset_matrix;
}

// ----------------------------------------------------------------------------

/* override */
//
//      Description:
//              This method is called when the deformer is created by the
//              "deformer" command. You can add to the cmds in the MDagModifier
//              cmd in order to hook up any additional nodes that your node needs
//              to operate.
//
//              In this example, we create a locator and attach its matrix attribute
//              to the matrix input on the offset node. The locator is used to
//              set the direction and scale of the random field.
//
//      Description:
//              This method is optional.
//
MStatus Offset_dfm::accessoryNodeSetup(MDagModifier& cmd)
{
    MStatus result;

    // hook up the accessory node
    //
    MObject objLoc = cmd.createNode(MString("locator"),
                                    MObject::kNullObj,
                                    &result);

    if (MS::kSuccess == result) {
        MFnDependencyNode fnLoc(objLoc);
        MString attrName;
        attrName.set("matrix");
        MObject attrMat = fnLoc.attribute(attrName);

        result = cmd.connect(objLoc,
                             attrMat,
                             this->thisMObject(),
                             Offset_dfm::s_offset_matrix);
    }
    return result;
}
#endif

// ----------------------------------------------------------------------------

class Hidden_feature {
public:
    Hidden_feature() {}
    /*virtual*/ ~Hidden_feature() {}

    void fun(){
        std::cout << "test" << std::endl;
    }
};


void some_test_function()
{

    Hidden_feature cl;
    cl.fun();
    std::cout << "message " << std::endl;

}


// standard initialization procedures
//
MStatus initializePlugin( MObject obj )
{
    Hidden_feature cl;
    cl.fun();
    some_test_function();
    MStatus result;
    MFnPlugin plugin( obj, PLUGIN_COMPANY, "3.0", "Any");
    /*
    result = plugin.registerNode( "offset",
                                  Offset_dfm::s_id,
                                  Offset_dfm::creator,   // fun pointer
                                  Offset_dfm::initialize,// fun pointer
                                  MPxNode::kDeformerNode );
*/
    return result;
}

// ----------------------------------------------------------------------------

MStatus uninitializePlugin( MObject obj)
{
    MStatus result;
    MFnPlugin plugin( obj );
    //result = plugin.deregisterNode( Offset_dfm::s_id );
    return result;
}

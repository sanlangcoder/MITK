/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef _MITK_PlanarFigure_WRITER__H_
#define _MITK_PlanarFigure_WRITER__H_

#include <MitkPlanarFigureExports.h>
#include <itkProcessObject.h>
#include <mitkFileWriterWithInformation.h>
#include <mitkPlanarFigure.h>

class TiXmlElement;
namespace mitk
{
  /**
  * @brief XML-based writer for mitk::PlanarFigures
  *
  * XML-based writer for mitk::PlanarFigures.
  * @ingroup MitkPlanarFigureModule
  */
  class MITKPLANARFIGURE_EXPORT PlanarFigureWriter : public mitk::FileWriterWithInformation
  {
  public:
    mitkClassMacro(PlanarFigureWriter, mitk::FileWriter);

    mitkWriterMacro;

    itkFactorylessNewMacro(Self) itkCloneMacro(Self)

      typedef mitk::PlanarFigure InputType;

    typedef InputType::Pointer InputTypePointer;

    /**
    * Sets the filename of the file to write.
    * @param FileName the name of the file to write.
    */
    itkSetStringMacro(FileName);

    /**
    * @returns the name of the file to be written to disk.
    */
    itkGetStringMacro(FileName);

    /**
    * @warning multiple write not (yet) supported
    */
    itkSetStringMacro(FilePrefix);

    /**
    * @warning multiple write not (yet) supported
    */
    itkGetStringMacro(FilePrefix);

    /**
    * @warning multiple write not (yet) supported
    */
    itkSetStringMacro(FilePattern);

    /**
    * @warning multiple write not (yet) supported
    */
    itkGetStringMacro(FilePattern);

    using Superclass::SetInput;

    /**
    * Sets the 0'th input object for the filter.
    * @param input the first input for the filter.
    */
    void SetInput(InputType *input);

    /**
    * Sets the n'th input object for the filter. If num is
    * larger than GetNumberOfInputs() the number of inputs is
    * resized appropriately.
    * @param input the n'th input for the filter.
    */
    void SetInput(const unsigned int &num, InputType *input);

    /**
    * @returns the 0'th input object of the filter.
    */
    PlanarFigure *GetInput();

    /**
    * @param num the index of the desired output object.
    * @returns the n'th input object of the filter.
    */
    PlanarFigure *GetInput(const unsigned int &num);

    /**
    * @brief Return the possible file extensions for the data type associated with the writer
    */
    std::vector<std::string> GetPossibleFileExtensions() override;

    /**
    * @brief Return the extension to be added to the filename.
    */
    std::string GetFileExtension() override;

    /**
    * @brief Check if the Writer can write the Content of the
    */
    bool CanWriteDataType(DataNode *) override;

    /**
    * @brief Return the MimeType of the saved File.
    */
    std::string GetWritenMIMEType() override;

    /**
    * @brief Set the DataTreenode as Input. Important: The Writer always have a SetInput-Function.
    */
    virtual void SetInput(DataNode *);

    std::string GetSupportedBaseData() const override;

    /**
    * @returns whether the last write attempt was successful or not.
    */
    itkGetConstMacro(Success, bool);

    const char *GetDefaultFilename() override { return "PlanarFigure.pf"; }
    const char *GetFileDialogPattern() override { return "Planar Figure Files (*.pf)"; }
    const char *GetDefaultExtension() override { return ".pf"; }
    bool CanWriteBaseDataType(BaseData::Pointer data) override
    {
      return dynamic_cast<mitk::PlanarFigure *>(data.GetPointer());
    }
    void DoWrite(BaseData::Pointer data) override
    {
      if (CanWriteBaseDataType(data))
      {
        this->SetInput(dynamic_cast<mitk::PlanarFigure *>(data.GetPointer()));
        this->Update();
      }
    }

    /**
    @brief CAUTION: It's up to the user to call this function to release the
    memory buffer after use in case the file writer has written to its memory array.
    See mitkFileWriter base class. */
    void ReleaseMemory() override;

  protected:
    /**
    * Constructor.
    */
    PlanarFigureWriter();

    /**
    * Virtual destructor.
    */
    ~PlanarFigureWriter() override;

    /**
    * Writes the a .pf file in xml format that contains all input planar figures
    */
    void GenerateData() override;

    /**
    * Resizes the number of inputs of the writer.
    * The inputs are initialized by empty PlanarFigures
    * @param num the new number of inputs
    */
    virtual void ResizeInputs(const unsigned int &num);

    /**Documentation
    * \brief creates a TinyXML element that contains x, y, and z values
    *
    * \param[in] name the name of the XML element
    * \param[in] v the vector or point that contains the x, y and z values
    * \return returns a TiXmlElement named name and three attributes x, y and z.
    */
    TiXmlElement *CreateXMLVectorElement(const char *name, itk::FixedArray<mitk::ScalarType, 3> v);

    std::string m_FileName;
    std::string m_FilePrefix;
    std::string m_FilePattern;
    std::string m_Extension;
    std::string m_MimeType;
    bool m_Success;
  };
}

#endif

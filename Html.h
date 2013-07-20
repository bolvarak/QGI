///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef QGI_HTML_H
#define QGI_HTML_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QObject>
#include <QMap>
#include <QString>
#include <QStringList>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// QGI Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QGI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Structures ///////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This is the base element structure
	 * @brief QGI::Element()
	 */
	struct Element {

			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains the element's key/value pair attributes
			 * @brief QGI::Element::mAttributes
			 * @var QMap<QString, QString>
			 */
			QMap<QString, QString> mAttributes;

			/**
			 * @paragraph This property contain the element's properties
			 * @brief QGI::Element::mProperties
			 * @var QSringList
			 */
			QStringList mProperties;

			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This constructor simply sets up the stucture
			 * @brief Element::Element()
			 */
			Element()
			{}

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method adds an attribute to the structure
			 * @brief QGI::Element::addAttribute()
			 * @param QString strName
			 * @param QString strValue
			 * @return QGI::Element*
			 */
			Element* addAttribute(QString strName, QString strValue)
			{
				// Add the attribute into the structure instance
				this->mAttributes.insert(strName, strValue);
				// Return the structure instance
				return this;
			}

			/**
			 * @paragraph This method adds a property to the structure
			 * @brief QGI::Element::addProperty()
			 * @param QString strProperty
			 * @return QGI::Element*
			 */
			Element* addProperty(QString strProperty)
			{
				// Set the property into the structure instance
				this->mProperties.append(strProperty);
				// Remove duplicates
				this->mProperties.removeDuplicates();
				// Return the structure instance
				return this;
			}
	};

	/**
	 * @paragraph This structure generates self-closing tags such as link and meta tags
	 * @brief QGI::SelfClosingElement()
	 */
	struct SelfClosingElement : public Element
	{
			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains the tag type
			 * @brief QGI::Element::mType
			 * @var QString
			 */
			QString mType;

			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This contructor sets the element type into the strucure
			 * @brief QGI::SelfClosingElement()
			 * @param QString strType
			 */
			SelfClosingElement(QString strType)
			{
				// Set the element type into the structure instance
				this->mType = strType;
			}

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method builds the element and returns it
			 * @brief QGI::SelfClosingElement::toString()
			 * @return QString
			 */
			QString toString()
			{
				// Create the element string placeholder
				QString strElement = "<";
				// Add the type to the string
				strElement.append(this->mType);
				// Create the attributes iterator
				QMap<QString, QString>::iterator itrAttributes;
				// Loop through the attributes
				for (itrAttributes = this->mAttributes.begin(); itrAttributes != this->mAttributes.end(); ++itrAttributes) {
					// Add the attribute to the element
					strElement.append(QString(" %1=\"%2\"").arg(itrAttributes.key(), itrAttributes.value()));
				}
				// Loop through the properties
				foreach (QString strProperty, this->mProperties) {
					// Add the property to the element
					strElement.append(QString(" %1").arg(strProperty));
				}
				// Finalize the element
				strElement.append(">");
				// Return the element
				return strElement;
			}
	};

	/**
	 * @paragraph This structure generates normal tag elements like div and p
	 * @brief QGI::TagElement()
	 */
	struct TagElement : public Element
	{
			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains the element type
			 * @brief QGI::TagElement::mType
			 * @var QString
			 */
			QString mType;

			/**
			 * @paragraph This property tells the strcture whether or not the value is an attribute on in between the tags
			 * @brief QGI::TagElement::mValueIsAttribute
			 * @var bool
			 */
			bool mValueIsAttribute;

			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This constructor sets up the structure instance for normal tag generation
			 * @brief TagElement
			 * @param strType
			 * @param bValueIsAttribute
			 */
			TagElement(QString strType, bool bValueIsAttribute = true)
			{
				// Set the element type into the structure instance
				this->mType             = strType;
				// Set the value placement identifier into the structure instance
				this->mValueIsAttribute = bValueIsAttribute;
			}

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method builds and returns the HTML tag element
			 * @brief QGI::TagElement::toString()
			 * @return QString
			 */
			QString toString()
			{
				// Create the element string placeholder
				QString strElement = "<";
				// Add the type to the string
				strElement.append(this->mType);
				// Create the attributes iterator
				QMap<QString, QString>::iterator itrAttributes;
				// Loop through the attributes
				for (itrAttributes = this->mAttributes.begin(); itrAttributes != this->mAttributes.end(); ++itrAttributes) {
					// Check the key
					if ((itrAttributes.key() == "value") && (this->mValueIsAttribute == false)) {
						// Continue to the next iteration
						continue;
					}
					// Add the attribute to the element
					strElement.append(QString(" %1=\"%2\"").arg(itrAttributes.key(), itrAttributes.value()));
				}
				// Loop through the properties
				foreach (QString strProperty, this->mProperties) {
					// Add the property to the element
					strElement.append(QString(" %1").arg(strProperty));
				}
				// Check to see if the value is not an attribute
				if (this->mValueIsAttribute == false) {
					// Add the value
					strElement.append(this->mAttributes.value("value", ""));
				}
				// Finalize the element
				strElement.append(QString("</%1>").arg(this->mType));
				// Return the element
				return strElement;
			}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// HTML Class Definition ////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This class handles the generation of HTML elements
	 * @brief QGI::Html
	 */
	class Html : public QObject
	{
			/**
			 * Ensure this class is recognized as a Qt object
			 */
			Q_OBJECT

		///////////////////////////////////////////////////////////////////////
		/// Protected Methods & Properties ///////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		protected:

			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains the singleton instance of this class
			 * @brief QGI::Html::mInstance
			 * @var QGI::Html*
			 */
			static Html* mInstance;

		///////////////////////////////////////////////////////////////////////
		/// Public Methods & Properties //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////////
			/// Constants ////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////


			static QString InputButton;


			static QString InputCheckbox;


			static QString InputFile;


			static QString InputHidden;


			static QString InputImage;


			static QString InputPassword;


			static QString InputRadio;


			static QString InputReset;


			static QString InputSubmit;


			static QString InputText;


			static QString TagAnchor;


			static QString TagBody;


			static QString TagBold;


			static QString TagButton;


			static QString TagCaption;


			static QString TagDefinitionDescription;


			static QString TagDefinitionList;


			static QString TagDefinitionTerm;


			static QString TagDivider;


			static QString TagFieldset;


			static QString TagForm;


			static QString TagHead;


			static QString TagHeader1;


			static QString TagHeader2;


			static QString TagHeader3;


			static QString TagHeader4;


			static QString TagHeader5;


			static QString TagHtml;


			static QString TagInput;


			static QString TagItalics;


			static QString TagLabel;


			static QString TagLegend;


			static QString TagLink;


			static QString TagListItem;


			static QString TagMeta;


			static QString TagOrderedList;


			static QString TagParagraph;


			static QString TagScript;


			static QString TagSelect;


			static QString TagSpan;


			static QString TagStrong;


			static QString TagStyle;


			static QString TagTable;


			static QString TableBody;


			static QString TagTableData;


			static QString TagTableDataHeader;


			static QString TableFooter;


			static QString TagTableHeader;


			static QString TagTableRow;


			static QString TagTextarea;


			static QString TagTitle;


			static QString TagUnderline;


			static QString TagUnorderedList;

			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			///////////////////////////////////////////////////////////////////
			/// Singleton ////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method maintains access to the singleton instance of this class
			 * @brief QGI::Html::Instance()
			 * @param bool bReset [false]
			 * @return QGI::Html* QGI::Html::mInstance
			 */
			static Html* Instance(bool bReset = false);

			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			explicit Html(QObject* qoParent = 0);

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////



	};
}
#endif // HTML_H

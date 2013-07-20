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

			/**
			 * @paragraph This constant defines the text for the type attribute for the button input
			 * @brief QGI::Html::InputButton
			 * @var QString
			 */
			static QString InputButton;

			/**
			 * @paragraph This constant defines the text for the type attribute for the checkbox input
			 * @brief QGI::Html::InputCheckbox
			 * @var QString
			 */
			static QString InputCheckbox;

			/**
			 * @paragraph This constant defines the text for the type attribute for the file input
			 * @brief QGI::Html::InputFile
			 * @var QString
			 */
			static QString InputFile;

			/**
			 * @paragraph This constant defines the text for the type attribute for the hidden input
			 * @brief QGI::Html::InputHidden
			 * @var QString
			 */
			static QString InputHidden;

			/**
			 * @paragraph This constant defines the text for the type attribute for the image input
			 * @brief QGI::Html::InputImage
			 * @var QString
			 */
			static QString InputImage;

			/**
			 * @paragraph This constant defines the text for the type attribute for the password input
			 * @brief QGI::Html::InputPassword
			 * @var QString
			 */
			static QString InputPassword;

			/**
			 * @paragraph This constant defines the text for the type attribute for the radio input
			 * @brief QGI::Html::InputRadio
			 * @var QString
			 */
			static QString InputRadio;

			/**
			 * @paragraph This constant defines the text for the type attribute for the reset input
			 * @brief QGI::Html::InputReset
			 * @var QString
			 */
			static QString InputReset;

			/**
			 * @paragraph This constant defines the text for the type attribute for the submit input
			 * @brief QGI::Html::InputSubmit
			 * @var QString
			 */
			static QString InputSubmit;

			/**
			 * @paragraph This constant defines the text for the type attribute for the text input
			 * @brief QGI::Html::InputText
			 * @var QString
			 */
			static QString InputText;

			/**
			 * @paragraph This constant defines the text for the a tag
			 * @brief QGI::Html::TagAnchor
			 * @var QString
			 */
			static QString TagAnchor;

			/**
			 * @paragraph This constant defines the text for the body tag
			 * @brief QGI::Html::TagBody
			 * @var QString
			 */
			static QString TagBody;

			/**
			 * @paragraph This constant defines the text for the b tag
			 * @brief QGI::Html::TagBold
			 * @var QString
			 */
			static QString TagBold;

			/**
			 * @paragraph This constant defines the text for the button tag
			 * @brief QGI::Html::TagButton
			 * @var QString
			 */
			static QString TagButton;

			/**
			 * @paragraph This constant defines the text for the caption tag
			 * @brief QGI::Html::TagCaption
			 * @var QString
			 */
			static QString TagCaption;

			/**
			 * @paragraph This constant defines the text for the dd tag
			 * @brief QGI::Html::TagDefinitionDescription
			 * @var QString
			 */
			static QString TagDefinitionDescription;

			/**
			 * @paragraph This constant defines the text for the dl tag
			 * @brief QGI::Html::TagDefinitionList
			 * @var QString
			 */
			static QString TagDefinitionList;

			/**
			 * @paragraph This constant defines the text for the dt tag
			 * @brief QGI::Html::TagDefinitionTerm
			 * @var QString
			 */
			static QString TagDefinitionTerm;

			/**
			 * @paragraph This constant defines the text for the div tag
			 * @brief QGI::Html::TagDivider
			 * @var QString
			 */
			static QString TagDivider;

			/**
			 * @paragraph This constant defines the text for the fieldset tag
			 * @brief QGI::Html::TagFieldset
			 * @var QString
			 */
			static QString TagFieldset;

			/**
			 * @paragraph This constant defines the text for the form tag
			 * @brief QGI::Html::TagForm
			 * @var QString
			 */
			static QString TagForm;

			/**
			 * @paragraph This constant defines the text for the head tag
			 * @brief QGI::Html::TagHead
			 * @var QString
			 */
			static QString TagHead;

			/**
			 * @paragraph This constant defines the text for the h1 tag
			 * @brief QGI::Html::TagHeader1
			 * @var QString
			 */
			static QString TagHeader1;

			/**
			 * @paragraph This constant defines the text for the h2 tag
			 * @brief QGI::Html::TagHeader2
			 * @var QString
			 */
			static QString TagHeader2;

			/**
			 * @paragraph This constant defines the text for the h3 tag
			 * @brief QGI::Html::TagHeader3
			 * @var QString
			 */
			static QString TagHeader3;

			/**
			 * @paragraph This constant defines the text for the h4 tag
			 * @brief QGI::Html::TagHeader4
			 * @var QString
			 */
			static QString TagHeader4;

			/**
			 * @paragraph This constant defines the text for the h5 tag
			 * @brief QGI::Html::TagHeader5
			 * @var QString
			 */
			static QString TagHeader5;

			/**
			 * @paragraph This constant defines the text for the hr tag
			 * @brief QGI::Html::TagHorizontalRule
			 * @var QString
			 */
			static QString TagHorizontalRule;

			/**
			 * @paragraph This constant defines the text for the html tag
			 * @brief QGI::Html::TagHtml
			 * @var QString
			 */
			static QString TagHtml;

			/**
			 * @paragraph This constant defines the text for the input tag
			 * @brief QGI::Html::TagInput
			 * @var QString
			 */
			static QString TagInput;

			/**
			 * @paragraph This constant defines the text for the i tag
			 * @brief QGI::Html::TagItalics
			 * @var QString
			 */
			static QString TagItalics;

			/**
			 * @paragraph This constant defines the text for the label tag
			 * @brief QGI::Html::TagLabel
			 * @var QString
			 */
			static QString TagLabel;

			/**
			 * @paragraph This constant defines the text for the legend tag
			 * @brief QGI::Html::TagLegend
			 * @var QString
			 */
			static QString TagLegend;

			/**
			 * @paragraph This constant defines the text for the link tag
			 * @brief QGI::Html::TagLink
			 * @var QString
			 */
			static QString TagLink;

			/**
			 * @paragraph This constant defines the text for the li tag
			 * @brief QGI::Html::TagListItem
			 * @var QString
			 */
			static QString TagListItem;

			/**
			 * @paragraph This constant defines the text for the meta tag
			 * @brief QGI::Html::TagMeta
			 * @var QString
			 */
			static QString TagMeta;

			/**
			 * @paragraph This constant defines the text for the option tag
			 * @brief QGI::Html::TagOption
			 * @var QString
			 */
			static QString TagOption;

			/**
			 * @paragraph This constant defines the text for the ol tag
			 * @brief QGI::Html::TagOrderedList
			 * @var QString
			 */
			static QString TagOrderedList;

			/**
			 * @paragraph This constant defines the text for the p tag
			 * @brief QGI::Html::TagParagraph
			 * @var QString
			 */
			static QString TagParagraph;

			/**
			 * @paragraph This constant defines the text for the script tag
			 * @brief QGI::Html::TagScript
			 * @var QString
			 */
			static QString TagScript;

			/**
			 * @paragraph This constant defines the text for the select tag
			 * @brief QGI::Html::TagSelect
			 * @var QString
			 */
			static QString TagSelect;

			/**
			 * @paragraph This constant defines the text for the span tag
			 * @brief QGI::Html::TagSpan
			 * @var QString
			 */
			static QString TagSpan;

			/**
			 * @paragraph This constant defines the text for the strong tag
			 * @brief QGI::Html::TagStrong
			 * @var QString
			 */
			static QString TagStrong;

			/**
			 * @paragraph This constant defines the text for the style tag
			 * @brief QGI::Html::TagStyle
			 * @var QString
			 */
			static QString TagStyle;

			/**
			 * @paragraph This constant defines the text for the table tag
			 * @brief QGI::Html::TagTable
			 * @var QString
			 */
			static QString TagTable;

			/**
			 * @paragraph This constant defines the text for the tbody tag
			 * @brief QGI::Html::TagTableBody
			 * @var QString
			 */
			static QString TableBody;

			/**
			 * @paragraph This constant defines the text for the td tag
			 * @brief QGI::Html::TagTableData
			 * @var QString
			 */
			static QString TagTableData;

			/**
			 * @paragraph This constant defines the text for the th tag
			 * @brief QGI::Html::TagTableDataHeader
			 * @var QString
			 */
			static QString TagTableDataHeader;

			/**
			 * @paragraph This constant defines the text for the tfoot tag
			 * @brief QGI::Html::TagTableFooter
			 * @var QString
			 */
			static QString TableFooter;

			/**
			 * @paragraph This constant defines the text for the thead tag
			 * @brief QGI::Html::TagTableHeader
			 * @var QString
			 */
			static QString TagTableHeader;

			/**
			 * @paragraph This constant defines the text for the tr tag
			 * @brief QGI::Html::TagTableRow
			 * @var QString
			 */
			static QString TagTableRow;

			/**
			 * @paragraph This constant defines the text for the textarea tag
			 * @brief QGI::Html::TagTextarea
			 * @var QString
			 */
			static QString TagTextarea;

			/**
			 * @paragraph This constant defines the text for the title tag
			 * @brief QGI::Html::TagTitle
			 * @var QString
			 */
			static QString TagTitle;

			/**
			 * @paragraph This constant defines the text for the u tag
			 * @brief QGI::Html::TagUnderline
			 * @var QString
			 */
			static QString TagUnderline;

			/**
			 * @paragraph This constant defines the text for the ul tag
			 * @brief QGI::Html::TagUnorderedList
			 * @var QString
			 */
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

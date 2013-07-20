///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Html.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Globals //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QGI::Html* QGI::Html::mInstance = NULL;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constants ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static QString QGI::Html::InputButton              = "button";
static QString QGI::Html::InputCheckbox            = "checkbox";
static QString QGI::Html::InputFile                = "file";
static QString QGI::Html::InputHidden              = "hidden";
static QString QGI::Html::InputImage               = "image";
static QString QGI::Html::InputPassword            = "password";
static QString QGI::Html::InputRadio               = "radio";
static QString QGI::Html::InputReset               = "reset";
static QString QGI::Html::InputSubmit              = "submit";
static QString QGI::Html::InputText                = "text";
static QString QGI::Html::TagAnchor                = "a";
static QString QGI::Html::TagBody                  = "body";
static QString QGI::Html::TagBold                  = "b";
static QString QGI::Html::TagButton                = "button";
static QString QGI::Html::TagCaption               = "caption";
static QString QGI::Html::TagDefinitionDescription = "dd";
static QString QGI::Html::TagDefinitionList        = "dl";
static QString QGI::Html::TagDefinitionTerm        = "dt";
static QString QGI::Html::TagDivider               = "div";
static QString QGI::Html::TagFieldset              = "fieldset";
static QString QGI::Html::TagForm                  = "form";
static QString QGI::Html::TagHead                  = "head";
static QString QGI::Html::TagHeader1               = "h1";
static QString QGI::Html::TagHeader2               = "h2";
static QString QGI::Html::TagHeader3               = "h3";
static QString QGI::Html::TagHeader4               = "h4";
static QString QGI::Html::TagHeader5               = "h5";
static QString QGI::Html::TagHtml                  = "html";
static QString QGI::Html::TagItalics               = "i";
static QString QGI::Html::TagInput                 = "input";
static QString QGI::Html::TagLabel                 = "label";
static QString QGI::Html::TagLegend                = "legend";
static QString QGI::Html::TagLink                  = "link";
static QString QGI::Html::TagListItem              = "li";
static QString QGI::Html::TagMeta                  = "meta";
static QString QGI::Html::TagOrderedList           = "ol";
static QString QGI::Html::TagParagraph             = "p";
static QString QGI::Html::TagScript                = "script";
static QString QGI::Html::TagSelect                = "select";
static QString QGI::Html::TagSpan                  = "span";
static QString QGI::Html::TagStrong                = "strong";
static QString QGI::Html::TagStyle                 = "style";
static QString QGI::Html::TagTable                 = "table";
static QString QGI::Html::TableBody                = "tbody";
static QString QGI::Html::TagTableData             = "td";
static QString QGI::Html::TagTableDataHeader       = "th";
static QString QGI::Html::TableFooter              = "tfoot";
static QString QGI::Html::TagTableHeader           = "thead";
static QString QGI::Html::TagTableRow              = "tr";
static QString QGI::Html::TagTextarea              = "textarea";
static QString QGI::Html::TagTitle                 = "title";
static QString QGI::Html::TagUnorderedList         = "ul";

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Singleton ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This method maintains access to the singleton instance of this class
 * @brief QGI::Html::Instance()
 * @param bool bReset [false]
 * @return QGI::Html* QGI::Html::mInstance
 */
QGI::Html* QGI::Html::Instance(bool bReset)
{
	// Check for an existing instance or a reset notification
	if ((mInstance == NULL) || (bReset == true)) {
		// Create a new instance
		mInstance = new QGI::Html();
	}
	// Return the instance
	return mInstance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QGI::Html::Html(QObject* qoParent) : QObject(qoParent){}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Methods //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




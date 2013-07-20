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

QString QGI::Html::InputButton              = "button";
QString QGI::Html::InputCheckbox            = "checkbox";
QString QGI::Html::InputFile                = "file";
QString QGI::Html::InputHidden              = "hidden";
QString QGI::Html::InputImage               = "image";
QString QGI::Html::InputPassword            = "password";
QString QGI::Html::InputRadio               = "radio";
QString QGI::Html::InputReset               = "reset";
QString QGI::Html::InputSubmit              = "submit";
QString QGI::Html::InputText                = "text";
QString QGI::Html::TagAnchor                = "a";
QString QGI::Html::TagBody                  = "body";
QString QGI::Html::TagBold                  = "b";
QString QGI::Html::TagButton                = "button";
QString QGI::Html::TagCaption               = "caption";
QString QGI::Html::TagDefinitionDescription = "dd";
QString QGI::Html::TagDefinitionList        = "dl";
QString QGI::Html::TagDefinitionTerm        = "dt";
QString QGI::Html::TagDivider               = "div";
QString QGI::Html::TagFieldset              = "fieldset";
QString QGI::Html::TagForm                  = "form";
QString QGI::Html::TagHead                  = "head";
QString QGI::Html::TagHeader1               = "h1";
QString QGI::Html::TagHeader2               = "h2";
QString QGI::Html::TagHeader3               = "h3";
QString QGI::Html::TagHeader4               = "h4";
QString QGI::Html::TagHeader5               = "h5";
QString QGI::Html::TagHorizontalRule        = "hr";
QString QGI::Html::TagHtml                  = "html";
QString QGI::Html::TagItalics               = "i";
QString QGI::Html::TagInput                 = "input";
QString QGI::Html::TagLabel                 = "label";
QString QGI::Html::TagLegend                = "legend";
QString QGI::Html::TagLink                  = "link";
QString QGI::Html::TagListItem              = "li";
QString QGI::Html::TagMeta                  = "meta";
QString QGI::Html::TagOption                = "option";
QString QGI::Html::TagOrderedList           = "ol";
QString QGI::Html::TagParagraph             = "p";
QString QGI::Html::TagScript                = "script";
QString QGI::Html::TagSelect                = "select";
QString QGI::Html::TagSpan                  = "span";
QString QGI::Html::TagStrong                = "strong";
QString QGI::Html::TagStyle                 = "style";
QString QGI::Html::TagTable                 = "table";
QString QGI::Html::TableBody                = "tbody";
QString QGI::Html::TagTableData             = "td";
QString QGI::Html::TagTableDataHeader       = "th";
QString QGI::Html::TableFooter              = "tfoot";
QString QGI::Html::TagTableHeader           = "thead";
QString QGI::Html::TagTableRow              = "tr";
QString QGI::Html::TagTextarea              = "textarea";
QString QGI::Html::TagTitle                 = "title";
QString QGI::Html::TagUnorderedList         = "ul";

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




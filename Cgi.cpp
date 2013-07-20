///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Cgi.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Globals //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QGI::Cgi* QGI::Cgi::mInstance               = NULL;
QString QGI::Cgi::ContentImageGIF           = "image/gif";
QString QGI::Cgi::ContentImageJPEG          = "image/jpeg";
QString QGI::Cgi::ContentImageJPG           = "image/jpg";
QString QGI::Cgi::ContentImagePNG           = "image/png";
QString QGI::Cgi::ContentImageSVG           = "image/svg+xml";
QString QGI::Cgi::ContentImageTIFF          = "image/tiff";
QString QGI::Cgi::ContentFont               = "application/font";
QString QGI::Cgi::ContentFontEOT            = "application/vnd.ms-fontobject";
QString QGI::Cgi::ContentFontOTF            = "font/opentype";
QString QGI::Cgi::ContentFontTTF            = "font/ttf";
QString QGI::Cgi::ContentFontWOFF           = "font/woff";
QString QGI::Cgi::ContentScriptECMAS        = "text/ecmascript";
QString QGI::Cgi::ContentScriptVB           = "text/vbscript";
QString QGI::Cgi::ContentTypeCSS            = "text/css";
QString QGI::Cgi::ContentTypeHTML           = "text/html";
QString QGI::Cgi::ContentTypeJS             = "text/javascript";
QString QGI::Cgi::ContentTypeJSON           = "application/json";
QString QGI::Cgi::ContentTypeText           = "text/plain";
QString QGI::Cgi::ContentTypeXML            = "text/xml";
QString QGI::Cgi::HeaderComSpec             = "COMSPEC";
QString QGI::Cgi::HeaderDocumentRoot        = "DOCUMENT_ROOT";
QString QGI::Cgi::HeaderGatewayInterface    = "GATEWAY_INTERFACE";
QString QGI::Cgi::HeaderHttpAccept          = "HTTP_ACCEPT";
QString QGI::Cgi::HeaderHttpAcceptEncoding  = "HTTP_ACCEPT_ENCODING";
QString QGI::Cgi::HeaderHttpAcceptLanguage  = "HTTP_ACCEPT_LANGUAGE";
QString QGI::Cgi::HeaderHttpConnection      = "HTTP_CONNECTION";
QString QGI::Cgi::HeaderHttpCookie          = "HTTP_COOKIE";
QString QGI::Cgi::HeaderHttpHost            = "HTTP_HOST";
QString QGI::Cgi::HeaderHttpUserAgent       = "HTTP_USER_AGENT";
QString QGI::Cgi::HeaderPath                = "PATH";
QString QGI::Cgi::HeaderQueryString         = "QUERY_STRING";
QString QGI::Cgi::HeaderRemoteAddress       = "REMOTE_ADDR";
QString QGI::Cgi::HeaderRemotePort          = "REMOTE_PORT";
QString QGI::Cgi::HeaderRequestMethod       = "REQUEST_METHOD";
QString QGI::Cgi::HeaderRequestUri          = "REQUEST_URI";
QString QGI::Cgi::HeaderScriptFilename      = "SCRIPT_FILENAME";
QString QGI::Cgi::HeaderScriptName          = "SCRIPT_NAME";
QString QGI::Cgi::HeaderServerAddress       = "SERVER_ADDR";
QString QGI::Cgi::HeaderServerAdministrator = "SERVER_ADMIN";
QString QGI::Cgi::HeaderServerName          = "SERVER_NAME";
QString QGI::Cgi::HeaderServerPort          = "SERVER_PORT";
QString QGI::Cgi::HeaderServerProtocol      = "SERVER_PROTOCOL";
QString QGI::Cgi::HeaderServerSignature     = "SERVER_SIGNATURE";
QString QGI::Cgi::HeaderServerSoftware      = "SERVER_SOFTWARE";
QString QGI::Cgi::MethodDelete              = "DELETE";
QString QGI::Cgi::MethodGet                 = "GET";
QString QGI::Cgi::MethodHead                = "HEAD";
QString QGI::Cgi::MethodPost                = "POST";
QString QGI::Cgi::MethodPut                 = "PUT";

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Singleton ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This method maintains access to the singleton instance of this class
 * @brief QGI::Cgi::Instance()
 * @param bool bReset [false]
 * @param QObject* qoParent [0]
 * @return QGI::Cgi* QGI::Cgi::mInstance
 */
QGI::Cgi* QGI::Cgi::Instance(bool bReset, QObject* qoParent)
{
  // Check for an existing instance or a reset notification
	if ((mInstance == NULL) || (bReset == true)) {
		// Create a new instance
		mInstance = new QGI::Cgi(qoParent);
	}
	// Return the instance
	return mInstance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This constructor sets up the class to read the HTTP headers and interact with the QtCGI
 * @brief QGI::Cgi::QtCGI()
 * @param QObject* qoParent [0]
 */
QGI::Cgi::Cgi(QObject* qoParent) : QObject(qoParent)
{
	// Process the request and return
	this->ProcessHeaders() // Headers
		->ProcessCookies()   // Cookies
		->ProcessGet()       // Query String
		->ProcessPost();     // POST data
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This method processes the cookies into the instance
 * @brief QGI::Cgi::ProcessCookies()
 * @return QGI::Cgi* QGI::Cgi::mInstance
 */
QGI::Cgi* QGI::Cgi::ProcessCookies()
{
	// Load the cookies
	QString strCookies = this->mRequestHeaders.value(QGI::Cgi::HeaderHttpCookie);
	// Check for cookies
	if (!strCookies.isEmpty()) {
		// Set the cookies into the instance
		this->mCookies = this->DecodeQuery(strCookies, ";");
	}
	// Return the instance
	return this;
}

/**
 * @paragraph This method processes the QUERY_STRING into the instance
 * @brief QGI::Cgi::ProcessGet()
 * @return QGI::Cgi* QGI::Cgi::mInstance
 */
QGI::Cgi* QGI::Cgi::ProcessGet()
{
	// Load the Query String
	QString strQuery = this->mRequestHeaders.value(QGI::Cgi::HeaderQueryString);
	// Check for a query string
	if (!strQuery.isEmpty()) {
		// Set the GET variables into the instance
		this->mGetParameters = this->DecodeQuery(strQuery);
	}
	// Return the instance
	return this;
}

/**
 * @paragraph This method processes the request headers into the instance
 * @brief QGI::Cgi::ProcessHeaders()
 * @return QGI::Cgi* QGI::Cgi::mInstance
 */
QGI::Cgi* QGI::Cgi::ProcessHeaders()
{
	// Add the DOCUMENT_ROOT header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderDocumentRoot,        QString(qgetenv(QGI::Cgi::HeaderDocumentRoot.toLatin1().data())));
	// Add the GATEWAY_INTERFACE header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderGatewayInterface,    QString(qgetenv(QGI::Cgi::HeaderGatewayInterface.toLatin1().data())));
	// Add the HTTP_ACCEPT header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderHttpAccept,          QString(qgetenv(QGI::Cgi::HeaderHttpAccept.toLatin1().data())));
	// Add the HTTP_ACCEPT_ENCODING header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderHttpAcceptEncoding,  QString(qgetenv(QGI::Cgi::HeaderHttpAcceptEncoding.toLatin1().data())));
	// Add the HTTP_ACCEPT_LANGUAGE header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderHttpAcceptLanguage,  QString(qgetenv(QGI::Cgi::HeaderHttpAcceptLanguage.toLatin1().data())));
	// Add the HTTP_CONNECTION header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderHttpConnection,      QString(qgetenv(QGI::Cgi::HeaderHttpConnection.toLatin1().data())));
	// Add the HTTP_COOKIE header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderHttpCookie,          QString(qgetenv(QGI::Cgi::HeaderHttpCookie.toLatin1().data())));
	// Add the HTTP_HOST header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderHttpHost,            QString(qgetenv(QGI::Cgi::HeaderHttpHost.toLatin1().data())));
	// Add the HTTP_USER_AGENT header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderHttpUserAgent,       QString(qgetenv(QGI::Cgi::HeaderHttpUserAgent.toLatin1().data())));
	// Add the PATH header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderPath,                QString(qgetenv(QGI::Cgi::HeaderPath.toLatin1().data())));
	// Add the QUERY_STRING header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderQueryString,         QString(qgetenv(QGI::Cgi::HeaderQueryString.toLatin1().data())));
	// Add the REMOTE_ADDR header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderRemoteAddress,       QString(getenv(QGI::Cgi::HeaderRemoteAddress.toLatin1().data())));
	// Add the REMOTE_PORT header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderRemotePort,          QString(qgetenv(QGI::Cgi::HeaderRemotePort.toLatin1().data())));
	// Add the REQUEST_METHOD header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderRequestMethod,       QString(qgetenv(QGI::Cgi::HeaderRequestMethod.toUpper().toLatin1().data())));
	// Add the REQUEST_URI header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderRequestUri,          QString(qgetenv(QGI::Cgi::HeaderRequestUri.toLatin1().data())));
	// Add the SCRIPT_FILENAME header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderScriptFilename,      QString(qgetenv(QGI::Cgi::HeaderScriptFilename.toLatin1().data())));
	// Add the SCRIPT_NAME header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderScriptName,          QString(qgetenv(QGI::Cgi::HeaderScriptName.toLatin1().data())));
	// Add the SERVER_ADDR header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderServerAddress,       QString(qgetenv(QGI::Cgi::HeaderServerAddress.toLatin1().data())));
	// Add the SERVER_ADMIN header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderServerAdministrator, QString(qgetenv(QGI::Cgi::HeaderServerAdministrator.toLatin1().data())));
	// Add the SERVER_NAME header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderServerName,          QString(qgetenv(QGI::Cgi::HeaderServerName.toLatin1().data())));
	// Add the SERVER_PORT header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderServerPort,          QString(qgetenv(QGI::Cgi::HeaderServerPort.toLatin1().data())));
	// Add the SERVER_PROTOCOL header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderServerProtocol,      QString(qgetenv(QGI::Cgi::HeaderServerProtocol.toLatin1().data())));
	// Add the SERVER_SIGNATURE header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderServerSignature,     QString(qgetenv(QGI::Cgi::HeaderServerSignature.toLatin1().data())));
	// Add the SERVER_SOFTWARE header
	this->mRequestHeaders.insert(QGI::Cgi::HeaderServerSoftware,      QString(qgetenv(QGI::Cgi::HeaderServerSoftware.toLatin1().data())));
	// Return the instance
	return this;
}

/**
 * @paragraph This method processes the POST data into the instance
 * @brief QGI::Cgi::ProcessPost()
 * @return QGI::Cgi* QGI::Cgi::mInstance
 */
QGI::Cgi* QGI::Cgi::ProcessPost()
{
	// Make sure this is a POST request
	if (this->mRequestHeaders.value(QGI::Cgi::HeaderRequestMethod).toUpper() == QGI::Cgi::MethodPost) {
		// Create the post data placeholder
		std::string strPostData;
		// Loop throug the POST lines
		std::getline(std::cin, strPostData);
		// Make sure we don't have an empty POST set
		if (!QString::fromStdString(strPostData).isEmpty()) {
			// Set the POST data into the instance
			this->mPostParameters = this->DecodeQuery(QString().fromStdString(strPostData));
		}
	}
	// Return the instance
	return this;
}

/**
 * @paragraph This method writes the content body to the browser/socket/stream
 * @brief QGI::Cgi::SendContent()
 * @return QGI::Cgi* QGI::Cgi::mInstance
 */
QGI::Cgi* QGI::Cgi::SendContent()
{
	// Write the content
	std::cout << this->mContent.toStdString() << std::endl;
	// Return the instance
	return this;
}

/**
 * @paragraph This method writes the response headers to the browser/socket/stream
 * @brief QGI::Cgi::SendHeaders()
 * @return QGI::Cgi* QGI::Cgi::mInstance
 */
QGI::Cgi* QGI::Cgi::SendHeaders()
{
	// Add the content length header
	this->AddResponseHeader("Content-Length", QString::number(this->mContent.length()));
	// Create the iterator
	QMap<QString, QString>::iterator itrHeaders;
	// Loop through the headers
	for (itrHeaders = this->mResponseHeaders.begin(); itrHeaders != this->mResponseHeaders.end(); ++itrHeaders) {
		// Print the header
		std::cout << itrHeaders.key().toStdString() << ": " << itrHeaders.value().toStdString() << "\r\n";
	}
	// Send an extra newline
	std::cout << "\r\n";
	// Return the instance
	return this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This method sets a response header into the instance
 * @brief QGI::Cgi::AddResponseHeader()
 * @param QString strName
 * @param QString strValue
 * @return QGI::Cgi* QGI::Cgi::mInstance
 */
QGI::Cgi* QGI::Cgi::AddResponseHeader(QString strName, QString strValue)
{
	// Set the response header into the instance
	this->mResponseHeaders.insert(strName, strValue);
	// Return the instance
	return this;
}

/**
 * @paragraph This method decodes a query string into a query map
 * @brief QGI::Cgi::DecodeQuery()
 * @param QString strQuery
 * @param QString strPairSeparator ["&"]
 * @return QMap<QString, QString>
 */
QMap<QString, QString> QGI::Cgi::DecodeQuery(QString strQuery, QString strPairSeparator)
{
	// Create the map placeholder
	QMap<QString, QString> qmQuery;
	// Split the parameters
	QStringList qslParameters = strQuery.split(strPairSeparator);
	// Loop through the parameters
	foreach (QString strPair, qslParameters) {
		// Split the key/value pair
		QStringList qslPair = strPair.split("=");
		// Set the pair into the map
		qmQuery.insert(QUrl::fromPercentEncoding(qslPair.at(0).toLatin1()).replace("+", " "), QUrl::fromPercentEncoding(qslPair.at(1).toLatin1()).replace("+", " "));
	}
	// Return the map
	return qmQuery;
}

/**
 * @paragraph This method converts a query map into a query string
 * @brief QGI::Cgi::EncodeQuery()
 * @param QMap<QString, QString> qmQuery
 * @param QString strPairGlue ["&"]
 * @return QString
 */
QString QGI::Cgi::EncodeQuery(QMap<QString, QString> qmQuery, QString strPairGlue)
{
	// Create the query placeholder
	QStringList qslQuery;
	// Loop through the parameters
	foreach (QString strKey, qmQuery) {
		// Create the pair list
		QStringList qslPair;
		// Add the key
		qslPair.append(QString(QUrl::toPercentEncoding(strKey)).replace(" ", "+"));
		// Add the value
		qslPair.append(QString(QUrl::toPercentEncoding(qmQuery.value(strKey))).replace(" ", "+"));
		// Append the pair to the query string
		qslQuery.append(qslPair.join("="));
	}
	// Return the query string
	return qslQuery.join(strPairGlue);
}

/**
 * @paragraph This method converts a query variant map into a query string
 * @brief QGI::Cgi::EncodeQuery()
 * @param QVariantMap qvmQuery
 * @param QString strPairGlue ["&"]
 * @return QString
 */
QString QGI::Cgi::EncodeQuery(QVariantMap qvmQuery, QString strPairGlue)
{
	// Create the query placeholder
	QStringList qslQuery;
	// Loop through the parameters
	foreach (QString strKey, qvmQuery.keys()) {
		// Create the pair list
		QStringList qslPair;
		// Add the keyt
		qslPair.append(QString(QUrl::toPercentEncoding(strKey)).replace(" ", "+"));
		// Add the valie
		qslPair.append(QString(QUrl::toPercentEncoding(qvmQuery.value(strKey).toString())).replace(" ", "+"));
		// Append the pair to the query string
		qslQuery.append(qslPair.join("="));
	}
	// Return the query string
	return qslQuery.join(strPairGlue);
}

/**
 * @paragraph This method writes the response to the browser/socket/stram
 * @brief QGI::Cgi::WriteResponse()
 * @return void
 */
void QGI::Cgi::WriteResponse()
{
	// Write the data to the requester
	this->SendHeaders()  // Headers
		->SendContent(); // Content
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Getters //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This method returns the current content from the instance
 * @brief QGI::Cgi::GetContent()
 * @return QString QGI::Cgi::mContent
 */
QString QGI::Cgi::GetContent()
{
	// Return the content from the instance
	return this->mContent;
}

/**
 * @paragraph This method returns a cookies from the instance if it exists
 * @brief QGI::Cgi::GetCookie()
 * @param QString strName
 * @return QString
 */
QString QGI::Cgi::GetCookie(QString strName)
{
	// Check for the cookie
	if (this->mCookies.contains(strName)) {
		// Return the cookie
		return this->mCookies.value(strName);
	}
	// Elsewise, return null
	return NULL;
}

/**
 * @paragraph This method returns the current cookie map from the instance
 * @brief QGI::Cgi::GetCookies()
 * @return QMap<QString, QString> QGI::Cgi::mCookies
 */
QMap<QString, QString> QGI::Cgi::GetCookies()
{
	// Return the current cookie map
	return this->mCookies;
}

/**
 * @paragraph This method returns a GET/POST parameter from the instance if it exists
 * @brief QGI::Cgi::GetParam()
 * @param QString strName
 * @return QString
 */
QString QGI::Cgi::GetParam(QString strName)
{
	// Check for the parameter in POST
	if (this->mPostParameters.contains(strName)) {
		// Return the POST parameter
		return this->mPostParameters.value(strName);
	}
	// Check for the parameter in GET
	if (this->mGetParameters.contains(strName)) {
		// Return the GET parameter
		return this->mGetParameters.value(strName);
	}
	// Elsewise, return null
	return NULL;
}

/**
 * @paragraph This method returns the current POST map from the instance
 * @brief QGI::Cgi::GetPostData()
 * @return QMap<QString, QString> QGI::Cgi::mPostParameters
 */
QMap<QString, QString> QGI::Cgi::GetPostData()
{
	// Return the POST data
	return this->mPostParameters;
}

/**
 * @paragraph This method returns the current GET map from the instance
 * @brief QGI::Cgi::GetQueryData()
 * @return QMap<QString, QString> QGI::Cgi::mGetParameters
 */
QMap<QString, QString> QGI::Cgi::GetQueryData()
{
	// Return the GET data
	return this->mGetParameters;
}

/**
 * @paragraph This method returns a request header from the instance if it exists
 * @brief QGI::Cgi::GetRequestHeader()
 * @param QString strName
 * @return QString
 */
QString QGI::Cgi::GetRequestHeader(QString strName)
{
	// Check to see if the request header exists
	if (this->mRequestHeaders.contains(strName)) {
		// Return the request header
		return this->mRequestHeaders.value(strName);
	}
	// Elsewise, return null
	return NULL;
}

/**
 * @paragraph This method returns the current request headers from the instance
 * @brief QGI::Cgi::GetRequestHeaders()
 * @return QMap<QString, QString> QGI::Cgi::mRequestHeaders
 */
QMap<QString, QString> QGI::Cgi::GetRequestHeaders()
{
	// Return the response headers
	return this->mRequestHeaders;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Setters //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @paragraph This method sets the response content into the instance
 * @brief QGI::Cgi::SetContent()
 * @param QString strContent
 * @return QGI::Cgi* QGI::Cgi::mInstance
 */
QGI::Cgi* QGI::Cgi::SetContent(QString strContent)
{
	// Set the contnt into the instance
	this->mContent = strContent;
	// Return the instane
	return this;
}

/**
 * @paragraph This method sets the content type header into the instance
 * @brief QGI::Cgi::SetContentType()
 * @param QString strContentType
 * @return QGI::Cgi* QGI::Cgi::mInstance
 */
QGI::Cgi* QGI::Cgi::SetContentType(QString strContentType)
{
	// Set the content type into the instance
	this->AddResponseHeader("Content-Type", strContentType);
	// Return the instance
	return this;
}

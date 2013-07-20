///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \author Travis Brown <tmbrown6@gmail.com> ////////////////////////////////////////////////////////////////////////
/// \version 1.0                              ///////////////////////////////////////////////////////////////////////
/// \title QtCGI                              //////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef QGI_CGI_H
#define QGI_CGI_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <QByteArray>
#include <QDebug>
#include <QMap>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QUrl>
#include <QVariant>
#include <QVariantMap>
#include <string>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// QGI Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace QGI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Cgi Class Definition /////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
 * @paragraph This class handles the interaction between the web browser and the application
 * @brief QtCGI
 */
	class Cgi : public QObject
	{
			/**
		 * Ensure this class is recognized by Qt
		 */
			Q_OBJECT

			///////////////////////////////////////////////////////////////////////////
			/// Protected Methods & Properties ///////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////

		protected:

			///////////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			/**
		 * @paragraph This property contains the singleton instance of this class
		 * @brief QGI::Cgi::mInstance
		 * @var QGI::Cgi*
		 */
			static QGI::Cgi* mInstance;

			/**
		 * @paragraph This property contains the response content
		 * @brief QGI::Cgi::mContent
		 * @var QString
		 */
			QString mContent;

			/**
		 * @paragraph This property contains the HTTP cookies
		 * @brief QGI::Cgi::mCookies
		 * @var QMap<QString, QString>
		 */
			QMap<QString, QString> mCookies;

			/**
		 * @paragraph This property contains the GET data
		 * @brief QGI::Cgi::mGetParameters
		 * @var QMap<QString, QString>
		 */
			QMap<QString, QString> mGetParameters;

			/**
		 * @paragraph This property contains the POST data
		 * @brief QGI::Cgi::mPostParameters
		 * @var QMap<QString, QString>
		 */
			QMap<QString, QString> mPostParameters;

			/**
		 * @paragraph This property contains the request headers from the client
		 * @brief QGI::Cgi::mRequestHeaders
		 * @var QMap<QString, QString>
		 */
			QMap<QString, QString> mRequestHeaders;

			/**
		 * @paragraph This property contains the response headers to send to the client
		 * @brief QGI::Cgi::mResponseHeaders
		 * @var QMap<QString, QString>
		 */
			QMap<QString, QString> mResponseHeaders;

			///////////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			/**
		 * @paragraph This method processes the HTTP_COOKIE from the header
		 * @brief QGI::Cgi::ProcessCookies()
		 * @return QGI::Cgi* QGI::Cgi::mInstance
		 */
			QGI::Cgi* ProcessCookies();

			/**
		 * @paragraph This method processes the QUERY_STRING from the header
		 * @brief QGI::Cgi::ProcessGet()
		 * @return QGI::Cgi* QGI::Cgi::mInstance
		 */
			QGI::Cgi* ProcessGet();

			/**
		 * @paragraph This method processes the request headers into the instance
		 * @brief QGI::Cgi::ProcessHeaders()
		 * @return QGI::Cgi* QGI::Cgi::mInstance
		 */
			QGI::Cgi* ProcessHeaders();

			/**
		 * @paragraph This method processes the POST data into the instance
		 * @brief QGI::Cgi::ProcessPost()
		 * @return QGI::Cgi* QGI::Cgi::mInstance
		 */
			QGI::Cgi* ProcessPost();

			/**
		 * @paragraph This method writes the content to the browser/socket/stream
		 * @brief QGI::Cgi::SendContent()
		 * @return QGI::Cgi* QGI::Cgi::mInstance
		 */
			QGI::Cgi* SendContent();

			/**
		 * @paragraph This method writes the response headers to the browser/socket/stream
		 * @brief QGI::Cgi::SendHeaders()
		 * @return QGI::Cgi* QGI::Cgi::mInstance
		 */
			QGI::Cgi* SendHeaders();

			///////////////////////////////////////////////////////////////////////////
			/// Public Methods & Properties //////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			/**
		 * @paragraph This property contains the header type for GIF
		 * @brief QGI::Cgi::ContentImageGIF
		 * @var QString
		 */
			static QString ContentImageGIF;

			/**
		 * @paragraph This property contains the header type for JPEG
		 * @brief QGI::Cgi::ContentImageJPEG
		 * @var QString
		 */
			static QString ContentImageJPEG;

			/**
		 * @paragraph This property contains the header type for JPG
		 * @brief QGI::Cgi::ContentImageJPG
		 * @var QString
		 */
			static QString ContentImageJPG;

			/**
		 * @paragraph This property contains the header type for PNG
		 * @brief QGI::Cgi::ContentImagePNG
		 * @var QString
		 */
			static QString ContentImagePNG;

			/**
		 * @paragraph Thie property contains the header type for SVG
		 * @brief QGI::Cgi::ContentImageSVG
		 * @var QString
		 */
			static QString ContentImageSVG;

			/**
		 * @paragraph This property contains the header type for TIFF
		 * @brief QGI::Cgi::ContentImageTIFF
		 * @var QString
		 */
			static QString ContentImageTIFF;

			/**
		 * @paragraph This property contins the header type for FONT
		 * @brief QGI::Cgi::ContentFont
		 * @var QString
		 */
			static QString ContentFont;

			/**
		 * @paragraph This property contains the header type for EOT
		 * @brief QGI::Cgi::ContentFontEOT
		 * @var QString
		 */
			static QString ContentFontEOT;

			/**
		 * @paragraph This property contains the header type for OTF
		 * @brief QGI::Cgi::ContentFontOTF
		 * @var QString
		 */
			static QString ContentFontOTF;

			/**
		 * @paragraph This property contains the header type for TTF
		 * @brief QGI::Cgi::ContentFontTTF
		 * @var QString
		 */
			static QString ContentFontTTF;

			/**
		 * @paragraph This property contains the header type for WOFF
		 * @brief QGI::Cgi::ContentFontWOFF
		 * @var QString
		 */
			static QString ContentFontWOFF;

			/**
		 * @paragraph This property contains the header type for ECMAS
		 * @brief QGI::Cgi::ContentScriptECMAS
		 * @var QString
		 */
			static QString ContentScriptECMAS;

			/**
		 * @paragraph This property contains the header type for VB
		 * @brief QGI::Cgi::ContentScriptVB
		 * @var QString
		 */
			static QString ContentScriptVB;

			/**
		 * @paragraph This property contains the header type for CSS
		 * @brief QGI::Cgi::ContentTypeCSS
		 * @var QString
		 */
			static QString ContentTypeCSS;

			/**
		 * @paragraph This property contain the header type for HTML
		 * @brief QGI::Cgi::ContentTypeHTML
		 * @var QString
		 */
			static QString ContentTypeHTML;

			/**
		 * @paragraph This property contains the header type for JS
		 * @brief QGI::Cgi::ContentTypeJS
		 * @var QString
		 */
			static QString ContentTypeJS;

			/**
		 * @paragraph This property contains the header type for JSON
		 * @brief QGI::Cgi::ContentTypeJSON
		 * @var QString
		 */
			static QString ContentTypeJSON;

			/**
		 * @paragraph This property contains the header type for TXT
		 * @brief QGI::Cgi::ContentTypeText
		 * @var QString
		 */
			static QString ContentTypeText;

			/**
		 * @paragraph This property contains the header type for XML
		 * @brief QGI::Cgi::ContentTypeXML
		 * @var QString
		 */
			static QString ContentTypeXML;

			/**
		 * @paragraph This property contains the COMSPEC header name
		 * @brief QGI::Cgi::HeaderComSpec
		 * @var QString
		 */
			static QString HeaderComSpec;

			/**
		 * @paragraph This property contains the DOCUMENT_ROOT header name
		 * @brief QGI::Cgi::HeaderDocumentRoot
		 * @var QString
		 */
			static QString HeaderDocumentRoot;

			/**
		 * @paragraph This proeprty contains the GATEWAY_INTERFACE header name
		 * @brief QGI::Cgi::HeaderGatewayInterface
		 * @var QString
		 */
			static QString HeaderGatewayInterface;

			/**
		 * @paragraph This property contains the HTTP_ACCEPT header name
		 * @brief QGI::Cgi::HeaderHttpAccept
		 * @var QString
		 */
			static QString HeaderHttpAccept;

			/**
		 * @paragraph This property contains the HTTP_ACCEPT_ENCODING header name
		 * @brief QGI::Cgi::HeaderHttpAcceptEncoding
		 * @var QString
		 */
			static QString HeaderHttpAcceptEncoding;

			/**
		 * @paragraph This property contains the HTTP_ACCEPT_LANGUAGE header
		 * @brief QGI::Cgi::HeaderHttpAcceptLanguage
		 * @var QString
		 */
			static QString HeaderHttpAcceptLanguage;

			/**
		 * @paragraph This property contains the HTTP_CONNECTION header name
		 * @brief QGI::Cgi::HeaderHttpConnection
		 * @var QString
		 */
			static QString HeaderHttpConnection;

			/**
		 * @paragraph This property contains the HTTP_COOKIE header name
		 * @brief QGI::Cgi::HeaderHttpCookie
		 * @var QString
		 */
			static QString HeaderHttpCookie;

			/**
		 * @paragraph This property contains the HTTP_HOST header name
		 * @brief QGI::Cgi::HeaderHttpHost
		 * @var QString
		 */
			static QString HeaderHttpHost;

			/**
		 * @paragraph This property contains the HTTP_USER_AGENT header name
		 * @brief QGI::Cgi::HeaderHttpUserAgent
		 * @var QString
		 */
			static QString HeaderHttpUserAgent;

			/**
		 * @paragraph This property contains the PATH header name
		 * @brief QGI::Cgi::HeaderPath
		 */
			static QString HeaderPath;

			/**
		 * @paragraph This property contains the QUERY_STRING header name
		 * @brief QGI::Cgi::eaderQueryString
		 * @var QString
		 */
			static QString HeaderQueryString;

			/**
		 * @paragraph This property contains the REMOTE_ADDR header name
		 * @brief QGI::Cgi::HeaderRemoteAddress
		 * @var QString
		 */
			static QString HeaderRemoteAddress;

			/**
		 * @paragraph This property contain the REMOTE_PORT header name
		 * @brief QGI::Cgi::HeaderRemotePort
		 * @var QString
		 */
			static QString HeaderRemotePort;

			/**
		 * @paragraph This property contains the REQUEST_METHOD header name
		 * @brief QGI::Cgi::HeaderRequestMethod
		 * @var QString
		 */
			static QString HeaderRequestMethod;

			/**
		 * @paragraph This property contains the REQUEST_URI header name
		 * @brief QGI::Cgi::HeaderRequestUri
		 * @var QString
		 */
			static QString HeaderRequestUri;

			/**
		 * @paragraph This paragraph contains the SCRIPT_FILENAME header name
		 * @brief QGI::Cgi::HeaderScriptFilename
		 * @var QString
		 */
			static QString HeaderScriptFilename;

			/**
		 * @paragraph This property contains the SCRIPT_NAME header namr
		 * @brief QGI::Cgi::HeaderScriptName
		 * @var QString
		 */
			static QString HeaderScriptName;

			/**
		 * @paragraph This property contains the SERVER_ADDR header name
		 * @brief QGI::Cgi::HeaderServerAddress
		 * @var QString
		 */
			static QString HeaderServerAddress;

			/**
		 * @paragraph This property contians the SERVER_ADMIN header name
		 * @brief QGI::Cgi::HeaderServerAdministrator
		 * @var QString
		 */
			static QString HeaderServerAdministrator;

			/**
		 * @paragraph This property contains the SERVER_NAME header name
		 * @brief QGI::Cgi::HeaderServerName
		 * @var QString
		 */
			static QString HeaderServerName;

			/**
		 * @paragraph This property contains the SERVER_PORT header name
		 * @brief QGI::Cgi::HeaderServerPort
		 * @var QString
		 */
			static QString HeaderServerPort;

			/**
		 * @paragraph This property contains the SERVER_PROTOCOL header name
		 * @brief QGI::Cgi::HeaderServerProtocol
		 * @var QString
		 */
			static QString HeaderServerProtocol;

			/**
		 * @paragraph This property contains the SERVER_SIGNATURE header name
		 * @brief QGI::Cgi::HeaderServerSignature
		 * @var QString
		 */
			static QString HeaderServerSignature;

			/**
		 * @paragraph This property contains the SERVER_SOFTWARE header name
		 * @brief QGI::Cgi::HeaderServerSoftware
		 * @var QString
		 */
			static QString HeaderServerSoftware;

			/**
		 * @paragraph This property contains the DELETE data request method name
		 * @brief QGI::Cgi::MethodDelete
		 * @var QString
		 */
			static QString MethodDelete;

			/**
		 * @paragraph This property contains the GET data request method name
		 * @brief QGI::Cgi::MethodGet
		 * @var QString
		 */
			static QString MethodGet;

			/**
		 * @paragraph This property contains the HEAD data request method name
		 * @brief QGI::Cgi::MethodHead
		 * @var QString
		 */
			static QString MethodHead;

			/**
		 * @paragraph This property contains the POST data request method name
		 * @brief QGI::Cgi::MethodPost
		 * @var QString
		 */
			static QString MethodPost;

			/**
		 * @paragraph This property contains the PUT data request method name
		 * @brief QGI::Cgi::MethodPut
		 * @var QString
		 */
			static QString MethodPut;

			///////////////////////////////////////////////////////////////////////
			/// Singleton ////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			/**
		 * @paragraph This method maintains access to the singleton instance of this class
		 * @brief QGI::Cgi::Instance()
		 * @param bool bReset [false]
		 * @param QObject* qoParent [0]
		 * @return QGI::Cgi* QGI::Cgi::mInstance
		 */
			static QGI::Cgi* Instance(bool bReset = false, QObject* qoParent = 0);

			///////////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			/**
		 * @paragraph This constructor autmatically parses the HTTP headers and data
		 * @brief QGI::Cgi::QtCGI()
		 * @param QObject* qoParent [0]
		 */
			explicit Cgi(QObject* qoParent = 0);

			///////////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			/**
		 * @paragraph This method adds a response header to the instance
		 * @brief QGI::Cgi::AddResponseHeader()
		 * @param QString strName
		 * @param QString strValue
		 * @return QGI::Cgi* QGI::Cgi::mInstance
		 */
			QGI::Cgi* AddResponseHeader(QString strName, QString strValue);

			/**
		 * @paragraph This method decodes a query string into a query map
		 * @brief QGI::Cgi::DecodeQuery()
		 * @param QString strQuery
		 * @param QString strPairSeparator ["&"]
		 * @return QMap<QString, QString>
		 */
			QMap<QString, QString> DecodeQuery(QString strQuery, QString strPairSeparator = "&");

			/**
		 * @paragraph This method encodes a query map into a query string
		 * @brief QGI::Cgi::EncodeQuery()
		 * @param QMap<QString, QString> qmQuery
		 * @param QString strPairGlue ["&"]
		 * @return QString
		 */
			QString EncodeQuery(QMap<QString, QString> qmQuery, QString strPairGlue = "&");

			/**
		 * @paragraph This method encodes a query variant map into a query string
		 * @brief QGI::Cgi::EncodeQuery()
		 * @param QVariantMap qvmQuery
		 * @param QString strPairGlue ["&"]
		 * @return QString
		 */
			QString EncodeQuery(QVariantMap qvmQuery, QString strPairGlue = "&");

			/**
		 * @paragraph This method writes the HTTP response to the browser/socket
		 * @brief QGI::Cgi::WriteResponse()
		 * @return void
		 */
			void WriteResponse();

			///////////////////////////////////////////////////////////////////////
			/// Getters //////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			/**
		 * @paragraph This method returns the current response content in the instance
		 * @brief QGI::Cgi::GetContent()
		 * @return QString QGI::Cgi::mContent
		 */
			QString GetContent();

			/**
		 * @paragraph This method returns a cookie from the instance if one exists
		 * @brief QGI::Cgi::GetCookie()
		 * @param QString strName
		 * @return QString
		 */
			QString GetCookie(QString strName);

			/**
		 * @paragraph This method returns the current cookie map in the instance
		 * @brief QGI::Cgi::GetCookies()
		 * @return QMap<QString, QString> QGI::Cgi::mCookies
		 */
			QMap<QString, QString> GetCookies();

			/**
		 * @paragraph This method returns a GET/POST parameter from the instance if one exists
		 * @brief QGI::Cgi::GetParam()
		 * @param QString strName
		 * @return QString
		 */
			QString GetParam(QString strName);

			/**
		 * @paragraph This method returns the current POST map from the instance
		 * @brief QGI::Cgi::GetPostData()
		 * @return QMap<QString, QString> QGI::Cgi::mPostParameters
		 */
			QMap<QString, QString> GetPostData();

			/**
		 * @paragraph This method returns the current GET map from the instance
		 * @brief QGI::Cgi::GetQueryData()
		 * @return QMap<QString, QString> QGI::Cgi::mGetParameters
		 */
			QMap<QString, QString> GetQueryData();

			/**
		 * @paragraph This method returns a request header from the instance if one exists
		 * @brief QGI::Cgi::GetRequestHeader()
		 * @param QString strName
		 * @return QString
		 */
			QString GetRequestHeader(QString strName);

			/**
		 * @paragraph This method returns the current request header map in the instance
		 * @brief QGI::Cgi::GetRequestHeaders()
		 * @return QMap<QString, QString> QGI::Cgi::mRequestHeaders
		 */
			QMap<QString, QString> GetRequestHeaders();

			///////////////////////////////////////////////////////////////////////
			/// Setters //////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////

			/**
		 * @paragraph This method sets the response content into the instance
		 * @brief QGI::Cgi::SetContent()
		 * @param QString strContent
		 * @return QGI::Cgi* QGI::Cgi::mInstance
		 */
			QGI::Cgi* SetContent(QString strContent);

			/**
		 * @paragraph This method sets the content type header into the instance
		 * @brief QGI::Cgi::SetContentType()
		 * @param QString strContentType
		 * @return QGI::Cgi* QGI::Cgi::mInstance
		 */
			QGI::Cgi* SetContentType(QString strContentType = QGI::Cgi::ContentTypeHTML);

		signals:

		public slots:

	};
}

#endif // QGI_CGI_H

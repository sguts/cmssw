#include "CondTools/Ecal/interface/EcalClusterLocalContCorrXMLTranslator.h"
#include "CondTools/Ecal/interface/DOMHelperFunctions.h"
#include "FWCore/Concurrency/interface/Xerces.h"
#include "Utilities/Xerces/interface/XercesStrUtils.h"
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/sax/SAXException.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>

#include <iostream>
#include <sstream>
#include <fstream>

using namespace XERCES_CPP_NAMESPACE;
using namespace xuti;
using namespace std;

int  
EcalClusterLocalContCorrXMLTranslator::readXML(
           const string& filename,
	   EcalCondHeader& header,
	   EcalFunParams& record){

  cms::concurrency::xercesInitialize();

  XercesDOMParser* parser = new XercesDOMParser;
  parser->setValidationScheme( XercesDOMParser::Val_Never );
  parser->setDoNamespaces( false );
  parser->setDoSchema( false );
  
  parser->parse(filename.c_str());

  DOMDocument* xmlDoc = parser->getDocument();
  

  if (!xmlDoc) {
    std::cout << "EcalClusterLocalContCorrXMLTranslator::Error parsing document" << std::endl;
    return -1;
  }

  DOMElement* elementRoot = xmlDoc->getDocumentElement();

  xuti::readHeader(elementRoot, header);

  // need some extra code here

  delete parser;
  cms::concurrency::xercesTerminate();
  return 0;
}

std::string 
EcalClusterLocalContCorrXMLTranslator::dumpXML( const EcalCondHeader& header,
						const EcalFunParams& record ) {
    
  unique_ptr<DOMImplementation> impl( DOMImplementationRegistry::getDOMImplementation( cms::xerces::uStr("LS").ptr()));
  
  DOMLSSerializer* writer = impl->createLSSerializer();
  if( writer->getDomConfig()->canSetParameter( XMLUni::fgDOMWRTFormatPrettyPrint, true ))
    writer->getDomConfig()->setParameter( XMLUni::fgDOMWRTFormatPrettyPrint, true );
  
  DOMDocumentType* doctype = impl->createDocumentType( cms::xerces::uStr("XML").ptr(), 0, 0 );

  DOMDocument* doc = impl->createDocument( 0, cms::xerces::uStr("EcalClusterLocalContCorr").ptr(), doctype );
  
  DOMElement* root = doc->getDocumentElement();
  xuti::writeHeader(root, header);

  for( auto it : record.params()) {
    DOMElement* ECEC = 
      root->getOwnerDocument()->createElement( cms::xerces::uStr("ClusterLocal").ptr());
    root->appendChild(ECEC);

    WriteNodeWithValue(ECEC,Value_tag,it);
  }

  std::string dump = cms::xerces::toString( writer->writeToString( root ));
  doc->release();
  doctype->release();
  writer->release();

  return dump;
}

int 
EcalClusterLocalContCorrXMLTranslator::writeXML(
               const std::string& filename,         
	       const EcalCondHeader& header,
	       const EcalFunParams& record) {

  cms::concurrency::xercesInitialize();

  std::fstream fs(filename.c_str(),ios::out);
  fs<< dumpXML(header,record);

  cms::concurrency::xercesTerminate();

  return 0;  
}

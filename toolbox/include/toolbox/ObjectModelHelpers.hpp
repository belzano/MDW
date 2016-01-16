#pragma once

#include "toolbox/Types.hpp"

	///////////////////////////////////////////////

#define MAKE_ATTRIBUTE(attrtype, attrname)								\
	public:																\
		const attrtype& get##attrname() const { return _##attrname; }	\
		      attrtype& get##attrname()       { return _##attrname; }	\
		void set##attrname(const attrtype& other) { _##attrname = other;}\
																\
		attrtype _##attrname;

	///////////////////////////////////////////////
	// ptree -> type ->  ("attr", attributeMapper<ptree, int>(){ map(object, ptree) , map(ptree, object), int ::Obj(Obj*)  })
	// map<string, AttributeMapping<Ptree, Type>() > Registry<Ptree>
	/*
	class AttributeBridgeBase<class Object1, class Object2>
	{
		virtual void bridge(const Object1, Object2&) = 0;
		virtual void bridge(const Object2, Object1&) = 0;
	};
	
	template <class Object1, class Object2, class type>
	class AttributeBridge : AttributeBridgeBase<Object1, Object2>
	{
		void bridge(const Object1, Object2&) { bridge(object1.getter, object2); }
		void bridge(const Object2, Object1&) { bridge(object2, object1.getter);}
	};
	*/


#define MME_REGISTER_ATTRIBUTE_TO_PTREE(doctype, registry, attrtype, attrname)	BRIDGE_ATTRIBUTE_WITH_PTREE(doctype, attrname, get_##attrname)

	///////////////////////////////////////////////


#define MME_PTREEDOCUMENT_JSON_STORE_TO_FILE(filename, ptreeDoc)		\
{																		\
	toolbox::DataPtr aData;												\
	ptreeDoc.toJson(aData);												\
	storage->dataSet(filename, aData);									\
}

#define MME_PTREEDOCUMENT_JSON_STORE(storageKey, ptreeDoc, storage)		\
{																		\
	toolbox::DataPtr aData;												\
	ptreeDoc.toJson(aData);												\
	storage->dataSet(storageKey, aData);								\
}

#define MME_PTREEDOCUMENT_JSON_RETRIEVE(storageKey, ptreeDoc, storage)	\
{																		\
	toolbox::DataPtr aData = storage->dataGet(storageKey);				\
	if (nullptr != aData.get() )										\
	{																	\
		MDW_LOG_DEBUG("Parsing document [" << storageKey << "]"); 		\
		ptreeDoc.fromJson(aData);										\
	}																	\
	else																\
	{																	\
		MDW_LOG_ERROR("Unable to retrieve ["<< storageKey << "]");		\
	}																	\
}			


namespace toolbox
{
	typedef enum 
	{
		JSon,
		XML
	} SerializationType;

	///////////////////////////////////////////////	

/*
	template <class MySelf> 
	class PersistedPtreeDocument : public PtreeDocument<MySelf>
	{
	public:												
		PersistedPtreeDocument( toolbox::StorageCellPtr iStorage, 
								SerializationType iType = SerializationType::JSon) 
			: _storage(iStorage)
			, _serializationType(iType)
		{}
			
		void fromStorage()
		{												
			// read json from storage
			DataPtr aData;
			if (! _storage->dataGet(typeof(this), aData))
				return;
				
			// parse to this
			switch (_serializationType)
			{
				case SerializationType::JSon:
					PtreeDocument<MySelf>::fromJson(aData);		
					break;
				case SerializationType::JSon:
					PtreeDocument<MySelf>::fromXml(aData);		
					break;
			}
		}
		
		void toStorage()
		{
			// convert this to json
			DataPtr aData;
			switch (_serializationType)
			{
				case SerializationType::JSon:
					PtreeDocument<MySelf>::toJson(aData);		
					break;
				case SerializationType::JSon:
					PtreeDocument<MySelf>::toXml(aData);		
					break;
			}
			
			// write json to storage	
			_storage->dataSet(typeof(*this), aData);
		}

	private:
		toolbox::StorageCellPtr _storage;
		SerializationType _serializationType;
	};
*/
}

//
// Created by user on 2019-07-31.
//

#include "db.h"

namespace db {
using namespace std;
using namespace base;

void dump(shared_ptr<DataObject> object, const string& name) {
    ofstream output(name, ios::out | ios::binary);
    if (output.is_open()) {
        serialize(output, object);
        output.close();
    }
}

void serialize(ofstream& out, shared_ptr<DataObject>& object) {
    int size = base::get_obj_size(object->type());
    out.write((char*)object->type(), sizeof(DataType));
    if (object->type() != BOOLEAN) {
        DataObject *obj = object.get();
        out.write(((char *) obj) + 8, size);
    }
    switch (object->type()) {
        case INTEGER:
        case FLOAT:
        case ATOMIC_INTEGER:
        case ATOMIC_FLOAT:
        case ATOMIC_BOOLEAN:
            break;
        case BOOLEAN: {
            auto* data = static_cast<DataBoolean*>(object.get());
            int val = data->value();
            out.write((char*)&val, sizeof(int));
            break;
        }
        case STRING: {
            auto* data = static_cast<DataString*>(object.get());
            string val = data->value();
            int len = val.length();
            out.write((char*)&val, sizeof(int));
            out.write((char*)val.c_str(), sizeof(len));
            break;
        }
        case LIST: {
            auto* data = static_cast<List*>(object.get());
            int len = data->size();
            out.write((char*)&len, sizeof(int));
            for (int i = 0; i < len; ++i) {
                shared_ptr<DataObject> temp = data->get(i);
                serialize(out, temp);
            }
            break;
        }
        case TUPLE: {
            auto* data = static_cast<Tuple*>(object.get());
            int len = data->size();
            out.write((char*)&len, sizeof(int));
            for (int i = 0; i < len; ++i) {
                shared_ptr<DataObject> temp = data->get(i);
                serialize(out, temp);
            }
            break;
        }
        case DICT: {
            auto* data = static_cast<Dictionary *>(object.get());
            int len = data->count();
            out.write((char*)&len, sizeof(int));
            shared_ptr<Node*> dict = data->get_all();
            for (int i = 0; i < len; ++i) {
                shared_ptr<DataObject> k = dict.get()[i]->key();
                serialize(out, k);
                shared_ptr<DataObject> v = dict.get()[i]->val();
                serialize(out, v);
            }
            break;
        }
    }
}

shared_ptr<DataObject> deserialize(ifstream& in) {
    DataType type;
    in.read((char*)&type, sizeof(DataType));
    int size = base::get_obj_size(type);

    switch (type) {
        case INTEGER: {
            shared_ptr<DataInt> data = make_shared<DataInt>(0);
            DataInt* ptr = data.get();
            in.read(((char*)ptr)+8, size);
            return data;
        }
        case FLOAT: {
            shared_ptr<DataFloat> data = make_shared<DataFloat>(0);
            DataFloat* ptr = data.get();
            in.read(((char*)ptr)+8, size);
            return data;
        }
        case BOOLEAN: {
            int val;
            in.read((char*)&val, size);
            return val ? DataBoolean::True : DataBoolean::False;
        }
        case ATOMIC_INTEGER: {
            shared_ptr<AtomicInt> data = make_shared<AtomicInt>(0);
            AtomicInt* ptr = data.get();
            in.read(((char*)ptr)+8, size);
            return data;
        }
        case ATOMIC_FLOAT: {
            shared_ptr<AtomicFloat> data = make_shared<AtomicFloat>(0);
            AtomicFloat* ptr = data.get();
            in.read(((char*)ptr)+8, size);
            return data;
        }
        case ATOMIC_BOOLEAN: {
            shared_ptr<AtomicBoolean> data = make_shared<AtomicBoolean>(0);
            AtomicBoolean* ptr = data.get();
            in.read(((char*)ptr)+8, size);
            return data;
        }
        case STRING: {
            shared_ptr<DataString> data = make_shared<DataString>(string());
            DataString* ptr = data.get();
            in.read(((char*)ptr)+8, size);

            int len;
            in.read((char*)&len, size);

            char* contents = new char[len+1];
            in.read(contents, len);
            contents[len] = '\0';
            string str(contents);
            data->set(str);

            delete[] contents;
            return data;
        }
        case LIST: {
            shared_ptr<List> data = make_shared<List>();
            List* ptr = data.get();
            in.read(((char*)ptr)+8, size);

            int len;
            in.read((char*)&len, size);

            for (int i = 0; i < len; ++i)
                data->append(deserialize(in));
            // TODO: List should be replaced with pre-built list, not append value
            return data;
        }
        case TUPLE: {
            shared_ptr<List> data = make_shared<List>();
            List* ptr = data.get();
            in.read(((char*)ptr)+8, size);

            int len;
            in.read((char*)&len, size);

            for (int i = 0; i < len; ++i)
                data->append(deserialize(in));
            // TODO: List should be replaced with pre-built list, not append value

            shared_ptr<Tuple> tuple = make_shared<Tuple>(Tuple(data->get(), len));
            return tuple;
        }
        case DICT: {
            shared_ptr<Dictionary> data = make_shared<Dictionary>();
            Dictionary* ptr = data.get();
            in.read(((char*)ptr)+8, size);

            int len;
            in.read((char*)&len, size);

            for (int i = 0; i < len; ++i) {
                shared_ptr<DataObject> k = deserialize(in);
                shared_ptr<DataObject> v = deserialize(in);
                data->set(k, v);
            }

            return data;
        }
    }

    return nullptr;
}

shared_ptr<DataObject> load(const string& name) {
    ifstream input(name, ios::in | ios::binary);
    if (input.is_open()) {
        shared_ptr<DataObject> data = deserialize(input);
        input.close();
        return data;
    }
    return nullptr;
}

}

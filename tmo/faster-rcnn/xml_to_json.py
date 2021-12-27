from xml.etree.ElementTree import ElementTree, Element
import os
from typing import Union
from collections import OrderedDict
import xml.etree.ElementTree as ET
from json import dumps
# To use this code, make sure you
#
#     import json
#
# and then, to convert JSON from a string, do
#
#     result = welcome_from_dict(json.loads(json_string))

from typing import Any, List, TypeVar, Type, cast, Callable


T = TypeVar("T")


def from_str(x: Any) -> str:
    if isinstance(x, str):   
        return x
    else: return "0"


def to_class(c: Type[T], x: Any) -> dict:
    assert isinstance(x, c)
    return cast(Any, x).to_dict()


def from_list(f: Callable[[Any], T], x: Any) -> List[T]:
    if isinstance(x, list):
        return [f(y) for y in x]
    else:
        if x.get("actions")!=None:
            x.pop("actions")
        return[f(x)]

class Bndbox:
    xmin: float
    ymin: float
    xmax: float
    ymax: float
    

    def __init__(self, xmin: float, ymin: float, xmax: float, ymax: float) -> None:
        self.xmin = xmin
        self.ymin = ymin
        self.xmax = xmax
        self.ymax = ymax

    @staticmethod
    def from_dict(obj: Any) -> 'Bndbox':
        assert isinstance(obj, dict)
        xmin = float(from_str(obj.get("xmin")))
        ymin = float(from_str(obj.get("ymin")))
        xmax = float(from_str(obj.get("xmax")))
        ymax = float(from_str(obj.get("ymax")))
        return Bndbox(xmin, ymin, xmax, ymax)

    def to_dict(self) -> dict:
        result: dict = {}
        result["xmin"] = from_str(str(self.xmin))
        result["ymin"] = from_str(str(self.ymin))
        result["xmax"] = from_str(str(self.xmax))
        result["ymax"] = from_str(str(self.ymax))
        return result


class Object:
    name: str
    pose: str
    truncated: int
    difficult: int
    bndbox: Bndbox

    def __init__(self, name: str, pose: str, truncated: int, difficult: int, bndbox: Bndbox) -> None:
        self.name = name
        self.pose = pose
        self.truncated = truncated
        self.difficult = difficult
        self.bndbox = bndbox

    @staticmethod
    def from_dict(obj: Any) -> 'Object':
        assert isinstance(obj, dict)
        name = from_str(obj.get("name"))
        pose = from_str(obj.get("pose"))
        truncated = int(from_str(obj.get("truncated")))
        difficult = int(from_str(obj.get("difficult")))
        bndbox = Bndbox.from_dict(obj.get("bndbox"))
        return Object(name, pose, truncated, difficult, bndbox)

    def to_dict(self) -> dict:
        result: dict = {}
        result["name"] = from_str(self.name)
        result["pose"] = from_str(self.pose)
        result["truncated"] = from_str(str(self.truncated))
        result["difficult"] = from_str(str(self.difficult))
        result["bndbox"] = to_class(Bndbox, self.bndbox)
        return result


class Size:
    width: int
    height: int
    depth: int

    def __init__(self, width: int, height: int, depth: int) -> None:
        self.width = width
        self.height = height
        self.depth = depth

    @staticmethod
    def from_dict(obj: Any) -> 'Size':
        assert isinstance(obj, dict)
        width = int(from_str(obj.get("width")))
        height = int(from_str(obj.get("height")))
        depth = int(from_str(obj.get("depth")))
        return Size(width, height, depth)

    def to_dict(self) -> dict:
        result: dict = {}
        result["width"] = from_str(str(self.width))
        result["height"] = from_str(str(self.height))
        result["depth"] = from_str(str(self.depth))
        return result


class Source:
    database: str
    annotation: str
    image: str

    def __init__(self, database: str, annotation: str, image: str) -> None:
        self.database = database
        self.annotation = annotation
        self.image = image

    @staticmethod
    def from_dict(obj: Any) -> 'Source':
        assert isinstance(obj, dict)
        database = from_str(obj.get("database"))
        annotation = from_str(obj.get("annotation"))
        image = from_str(obj.get("image"))
        return Source(database, annotation, image)

    def to_dict(self) -> dict:
        result: dict = {}
        result["database"] = from_str(self.database)
        result["annotation"] = from_str(self.annotation)
        result["image"] = from_str(self.image)
        return result


class Annotation:
    folder: str
    filename: str
    source: Source
    size: Size
    segmented: int
    object: List[Object]

    def __init__(self, folder: str, filename: str, source: Source, size: Size, segmented: int, object: List[Object]) -> None:
        self.folder = folder
        self.filename = filename
        self.source = source
        self.size = size
        self.segmented = segmented
        self.object = object

    @staticmethod
    def from_dict(obj: Any) -> 'Annotation':
        assert isinstance(obj, dict)
        print(isinstance(obj, dict))
        print(obj.get("object"))
        folder = from_str(obj.get("folder"))
        filename = from_str(obj.get("filename"))
        source = Source.from_dict(obj.get("source"))
        size = Size.from_dict(obj.get("size"))
        segmented = int(from_str(obj.get("segmented")))
        object = from_list(Object.from_dict, obj.get("object"))
        return Annotation(folder, filename, source, size, segmented, object)

    def to_dict(self) -> dict:
        result: dict = {}
        result["folder"] = from_str(self.folder)
        result["filename"] = from_str(self.filename)
        result["source"] = to_class(Source, self.source)
        result["size"] = to_class(Size, self.size)
        result["segmented"] = from_str(str(self.segmented))
        result["object"] = from_list(lambda x: to_class(Object, x), self.object)
        return result


def welcome_from_dict(s: Any) -> Annotation:
    return Annotation.from_dict(s)


def welcome_to_dict(x: Annotation) -> Any:
    return to_class(Annotation, x)


class XmlToJson():
    def __init__(self,source_dir:str,destination:str) -> None:
        self.path=source_dir;
        self.json_path=destination
    def list_all_xml_file(self):
        self.xml_files=os.listdir(self.path)
        pass
    def etree_to_dict(self,root: Union[ElementTree, Element], include_root_tag=False):
        root = root.getroot() if isinstance(root, ElementTree) else root
        result = OrderedDict()
        if len(root) > 1 and len({child for child in root}) == 1:
            result[next(iter(root)).tag] = [self.etree_to_dict(child) for child in root]
        else:
            for child in root:
            # pass
                result[child.tag] = self.etree_to_dict(child) if len(list(child)) > 0 else (child.text or "")
                result.update(('@' + k, v) for k, v in root.attrib.items())
        return {root.tag: result} if include_root_tag else result  
    def write(self,file_name:str,xml:dict):
        with open (self.json_path+file_name,mode="w") as f:
            f.write(dumps(xml))
    def parse(self):
        self.list_all_xml_file()
        for xml_file in self.xml_files:
            print(self.path+xml_file)
            element=ET.parse(source=self.path+xml_file)
            xml_dict=self.etree_to_dict(element,include_root_tag=False)
            # print(str(xml_dict))
            print(type(xml_dict))
            annotation=Annotation.from_dict(xml_dict);
            json_file=xml_file.split(".")[0]+".json"
            self.write(json_file,annotation.to_dict())
            
if __name__ =="__main__":
     xml_to_json=XmlToJson(
         source_dir="/home/ubuntu/program/faster-rcnn/VOCdevkit/VOC2012/Annotations/",
         destination="/home/ubuntu/program/faster-rcnn/VOCdevkit/VOC2012/json/"
         )
     xml_to_json.parse();
     
     
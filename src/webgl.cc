#include <iostream>
#include <cstring>
using namespace std;

#include "webgl.h"
#include "image.h"
#include <node_buffer.h>

using namespace node;
using namespace v8;

namespace webgl {

v8::Handle<v8::Value> ThrowError(const char* msg) {
  return v8::ThrowException(v8::Exception::Error(v8::String::New(msg)));
}

static int SizeOfArrayElementForType(v8::ExternalArrayType type) {
  switch (type) {
  case v8::kExternalByteArray:
  case v8::kExternalUnsignedByteArray:
    return 1;
  case v8::kExternalShortArray:
  case v8::kExternalUnsignedShortArray:
    return 2;
  case v8::kExternalIntArray:
  case v8::kExternalUnsignedIntArray:
  case v8::kExternalFloatArray:
    return 4;
  default:
    return 0;
  }
}

inline void *getImageData(Local<Value> arg) {
  void *pixels=NULL;
    if(!arg->IsNull()) {
    Local<Object> obj = Local<Object>::Cast(arg);
    if(!obj->IsObject())
      ThrowException(JS_STR("Bad texture argument"));
    if(obj->GetIndexedPropertiesExternalArrayDataType()>0) {
      //cout<<"pixels as TypedArray, type="<<obj->GetIndexedPropertiesExternalArrayDataType()<<endl;
      pixels = obj->GetIndexedPropertiesExternalArrayData();
    }
    else {
      //cout<<"Pixels as Image data"<<endl;
      Image *image = ObjectWrap::Unwrap<Image>(arg->ToObject());
      pixels=image->GetData();
    }
  }
  return pixels;
}

JS_METHOD(Uniform1f) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  double x = args[1]->NumberValue();

  glUniform1f(location, x);
  return Undefined();
}

JS_METHOD(Uniform2f) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  double x = args[1]->NumberValue();
  double y = args[2]->NumberValue();

  glUniform2f(location, x, y);
  return Undefined();
}

JS_METHOD(Uniform3f) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  double x = args[1]->NumberValue();
  double y = args[2]->NumberValue();
  double z = args[3]->NumberValue();

  glUniform3f(location, x, y, z);
  return Undefined();
}

JS_METHOD(Uniform4f) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  double x = args[1]->NumberValue();
  double y = args[2]->NumberValue();
  double z = args[3]->NumberValue();
  double w = args[4]->NumberValue();

  glUniform4f(location, x, y, z, w);
  return Undefined();
}

JS_METHOD(Uniform1i) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  int x = args[1]->Int32Value();

  glUniform1i(location, x);
  return Undefined();
}

JS_METHOD(Uniform2i) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  int x = args[1]->Int32Value();
  int y = args[2]->Int32Value();

  glUniform2i(location, x, y);
  return Undefined();
}

JS_METHOD(Uniform3i) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  int x = args[1]->Int32Value();
  int y = args[2]->Int32Value();
  int z = args[3]->Int32Value();

  glUniform3i(location, x, y, z);
  return Undefined();
}

JS_METHOD(Uniform4i) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  int x = args[1]->Int32Value();
  int y = args[2]->Int32Value();
  int z = args[3]->Int32Value();
  int w = args[4]->Int32Value();

  glUniform4i(location, x, y, z, w);
  return Undefined();
}

JS_METHOD(Uniform1fv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length();

  glUniform1fv(location, num, (float*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(Uniform2fv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length()/2;

  glUniform2fv(location, num, (float*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(Uniform3fv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length()/3;

  glUniform3fv(location, num, (float*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(Uniform4fv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length()/4;

  glUniform4fv(location, num, (float*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(Uniform1iv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length();

  glUniform1iv(location, num, (int*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(Uniform2iv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length()/2;

  glUniform2iv(location, num, (int*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(Uniform3iv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length()/3;

  glUniform3iv(location, num, (int*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(Uniform4iv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length()/4;

  glUniform4iv(location, num, (int*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(PixelStorei) {
  HandleScope scope;

  int pname = args[0]->Int32Value();
  int param = args[1]->Int32Value();

  glPixelStorei(pname,param);

  return Undefined();
}

JS_METHOD(BindAttribLocation) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  int index = args[1]->Int32Value();
  String::Utf8Value name(args[2]);

  glBindAttribLocation(program, index, *name);

  return Undefined();
}


JS_METHOD(GetError) {
  HandleScope scope;

  return scope.Close(Number::New(glGetError()));
}


JS_METHOD(DrawArrays) {
  HandleScope scope;

  int mode = args[0]->Int32Value();
  int first = args[1]->Int32Value();
  int count = args[2]->Int32Value();

  glDrawArrays(mode, first, count);

  return Undefined();
}

JS_METHOD(UniformMatrix2fv) {
  HandleScope scope;

  GLint location = args[0]->Int32Value();
  GLboolean transpose = args[1]->BooleanValue();

  GLsizei count=0;
  GLfloat* data=NULL;

  if(args[2]->IsArray()) {
    Local<Array> value = Local<Array>::Cast(args[2]);
    count = value->GetIndexedPropertiesExternalArrayDataLength();
    data = (GLfloat*)value->GetIndexedPropertiesExternalArrayData();
  } else {
    Local<Object> value = Local<Object>::Cast(args[2]);
    count = value->GetIndexedPropertiesExternalArrayDataLength();
    data = (GLfloat*)value->GetIndexedPropertiesExternalArrayData();
  }

  if (count < 4) {
    return ThrowError("Not enough data for UniformMatrix2fv");
  }

  glUniformMatrix2fv(location, count / 4, transpose, data);

  return Undefined();
}

JS_METHOD(UniformMatrix3fv) {
  HandleScope scope;

  GLint location = args[0]->Int32Value();
  GLboolean transpose = args[1]->BooleanValue();
  GLsizei count=0;
  GLfloat* data=NULL;

  if(args[2]->IsArray()) {
    Local<Array> value = Local<Array>::Cast(args[2]);
    count = value->GetIndexedPropertiesExternalArrayDataLength();
    data = (GLfloat*)value->GetIndexedPropertiesExternalArrayData();
  } else {
    Local<Object> value = Local<Object>::Cast(args[2]);
    count = value->GetIndexedPropertiesExternalArrayDataLength();
    data = (GLfloat*)value->GetIndexedPropertiesExternalArrayData();
  }

  if (count < 9) {
    return ThrowError("Not enough data for UniformMatrix3fv");
  }

  glUniformMatrix3fv(location, count / 9, transpose, data);

  return Undefined();
}

JS_METHOD(UniformMatrix4fv) {
  HandleScope scope;

  GLint location = args[0]->Int32Value();
  GLboolean transpose = args[1]->BooleanValue();
  GLsizei count=0;
  GLfloat* data=NULL;

  if(args[2]->IsArray()) {
    Local<Array> value = Local<Array>::Cast(args[2]);
    count = value->GetIndexedPropertiesExternalArrayDataLength();
    data = (GLfloat*)value->GetIndexedPropertiesExternalArrayData();
  } else {
    Local<Object> value = Local<Object>::Cast(args[2]);
    count = value->GetIndexedPropertiesExternalArrayDataLength();
    data = (GLfloat*)value->GetIndexedPropertiesExternalArrayData();
  }

  if (count < 16) {
    return ThrowError("Not enough data for UniformMatrix4fv");
  }

  glUniformMatrix4fv(location, count / 16, transpose, data);

  return Undefined();
}

JS_METHOD(GenerateMipmap) {
  HandleScope scope;

  GLint target = args[0]->Int32Value();
  glGenerateMipmap(target);

  return Undefined();
}

JS_METHOD(GetAttribLocation) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  String::Utf8Value name(args[1]);

  return scope.Close(Number::New(glGetAttribLocation(program, *name)));
}


JS_METHOD(DepthFunc) {
  HandleScope scope;

  glDepthFunc(args[0]->Int32Value());

  return Undefined();
}


JS_METHOD(Viewport) {
  HandleScope scope;

  int x = args[0]->Int32Value();
  int y = args[1]->Int32Value();
  int width = args[2]->Int32Value();
  int height = args[3]->Int32Value();

  glViewport(x, y, width, height);

  return Undefined();

  return scope.Close(Number::New(glCreateShader(args[0]->Int32Value())));
}

JS_METHOD(CreateShader) {
  HandleScope scope;

  return scope.Close(Number::New(glCreateShader(args[0]->Int32Value())));
}


JS_METHOD(ShaderSource) {
  HandleScope scope;

  int id = args[0]->Int32Value();
  String::Utf8Value code(args[1]);

  const char* codes[1];
  codes[0] = *code;

  glShaderSource  (id, 1, codes, NULL);

  return Undefined();
}


JS_METHOD(CompileShader) {
  HandleScope scope;


  glCompileShader(args[0]->Int32Value());

  return Undefined();
}


JS_METHOD(GetShaderParameter) {
  HandleScope scope;

  int shader = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  int value = 0;
  switch (pname) {
  case GL_DELETE_STATUS:
  case GL_COMPILE_STATUS:
    glGetShaderiv(shader, pname, &value);
    return scope.Close(Boolean::New(static_cast<bool>(value)));
  case GL_SHADER_TYPE:
    glGetShaderiv(shader, pname, &value);
    return scope.Close(Number::New(static_cast<unsigned long>(value)));
  case GL_INFO_LOG_LENGTH:
  case GL_SHADER_SOURCE_LENGTH:
    glGetShaderiv(shader, pname, &value);
    return scope.Close(Number::New(static_cast<long>(value)));
  default:
    return ThrowException(Exception::TypeError(String::New("GetShaderParameter: Invalid Enum")));
  }
}

JS_METHOD(GetShaderInfoLog) {
  HandleScope scope;

  int id = args[0]->Int32Value();
  int Len = 1024;
  char Error[1024];
  glGetShaderInfoLog(id, 1024, &Len, Error);

  return scope.Close(String::New(Error));
}


JS_METHOD(CreateProgram) {
  HandleScope scope;

  return scope.Close(Number::New(glCreateProgram()));
}


JS_METHOD(AttachShader) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  int shader = args[1]->Int32Value();

  glAttachShader(program, shader);

  return Undefined();
}


JS_METHOD(LinkProgram) {
  HandleScope scope;

  glLinkProgram(args[0]->Int32Value());

  return Undefined();
}


JS_METHOD(GetProgramParameter) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  int pname = args[1]->Int32Value();

  int value = 0;
  switch (pname) {
  case GL_DELETE_STATUS:
  case GL_LINK_STATUS:
  case GL_VALIDATE_STATUS:
    glGetProgramiv(program, pname, &value);
    return scope.Close(Boolean::New(static_cast<bool>(value)));
  case GL_ATTACHED_SHADERS:
  case GL_ACTIVE_ATTRIBUTES:
  case GL_ACTIVE_UNIFORMS:
    glGetProgramiv(program, pname, &value);
    return scope.Close(Number::New(static_cast<long>(value)));
  default:
    return ThrowException(Exception::TypeError(String::New("GetProgramParameter: Invalid Enum")));
  }
}


JS_METHOD(GetUniformLocation) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  String::AsciiValue name(args[1]);

  return scope.Close(Number::New(glGetUniformLocation(program, *name)));
}


JS_METHOD(ClearColor) {
  HandleScope scope;

  double red = args[0]->NumberValue();
  double green = args[1]->NumberValue();
  double blue = args[2]->NumberValue();
  double alpha = args[3]->NumberValue();

  glClearColor(red, green, blue, alpha);

  return Undefined();
}


JS_METHOD(ClearDepth) {
  HandleScope scope;

  double depth = args[0]->NumberValue();

  glClearDepthf(depth);

  return Undefined();
}

JS_METHOD(Disable) {
  HandleScope scope;

  glDisable(args[0]->Int32Value());
  return Undefined();
}

JS_METHOD(Enable) {
  HandleScope scope;

  glEnable(args[0]->Int32Value());
  return Undefined();
}


JS_METHOD(CreateTexture) {
  HandleScope scope;

  GLuint texture;
  glGenTextures(1, &texture);
  return scope.Close(Number::New(texture));
}


JS_METHOD(BindTexture) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int texture = args[1]->Int32Value();

  glBindTexture(target, texture);
  return Undefined();
}


JS_METHOD(TexImage2D) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int level = args[1]->Int32Value();
  int internalformat = args[2]->Int32Value();
  int width = args[3]->Int32Value();
  int height = args[4]->Int32Value();
  int border = args[5]->Int32Value();
  int format = args[6]->Int32Value();
  int type = args[7]->Int32Value();
  void *pixels=getImageData(args[8]);

  if(pixels)
    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);

  return Undefined();
}


JS_METHOD(TexParameteri) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  int param = args[2]->Int32Value();

  glTexParameteri(target, pname, param);

  return Undefined();
}

JS_METHOD(TexParameterf) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  float param = args[2]->NumberValue();

  glTexParameterf(target, pname, param);

  return Undefined();
}


JS_METHOD(Clear) {
  HandleScope scope;

  glClear(args[0]->Int32Value());

  return Undefined();
}


JS_METHOD(UseProgram) {
  HandleScope scope;

  glUseProgram(args[0]->Int32Value());

  return Undefined();
}


JS_METHOD(CreateBuffer) {
  HandleScope scope;

  GLuint buffer;
  glGenBuffers(1, &buffer);
  return scope.Close(Number::New(buffer));
}


JS_METHOD(BindBuffer) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int buffer = args[1]->Int32Value();

  glBindBuffer(target, buffer);

  return Undefined();
}


JS_METHOD(CreateFramebuffer) {
  HandleScope scope;

  GLuint buffer;
  glGenFramebuffers(1, &buffer);
  return scope.Close(Number::New(buffer));
}


JS_METHOD(BindFramebuffer) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int buffer = args[1]->Int32Value();

  glBindFramebuffer(target, buffer);

  return Undefined();
}


JS_METHOD(FramebufferTexture2D) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int attachment = args[1]->Int32Value();
  int textarget = args[2]->Int32Value();
  int texture = args[3]->Int32Value();
  int level = args[4]->Int32Value();

  glFramebufferTexture2D(target, attachment, textarget, texture, level);

  return Undefined();
}


JS_METHOD(BufferData) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  if(args[1]->IsObject()) {
    Local<Object> obj = Local<Object>::Cast(args[1]);
    int usage = args[2]->Int32Value();

    int element_size = SizeOfArrayElementForType(obj->GetIndexedPropertiesExternalArrayDataType());
    int size = obj->GetIndexedPropertiesExternalArrayDataLength() * element_size;
    void* data = obj->GetIndexedPropertiesExternalArrayData();

    //    printf("BufferData %d %d %d\n", target, size, usage);
    glBufferData(target, size, data, usage);
  }
  else if(args[1]->IsNumber()) {
    int size = args[1]->Int32Value();
    int usage = args[2]->Int32Value();
    glBufferData(target, size, NULL, usage);
  }
  return Undefined();
}


JS_METHOD(BufferSubData) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int offset = args[1]->Int32Value();
  Local<Object> obj = Local<Object>::Cast(args[2]);

  int element_size = SizeOfArrayElementForType( obj->GetIndexedPropertiesExternalArrayDataType());
  int size = obj->GetIndexedPropertiesExternalArrayDataLength() * element_size;
  void* data = obj->GetIndexedPropertiesExternalArrayData();

  glBufferSubData(target, offset, size, data);

  return Undefined();
}


JS_METHOD(BlendEquation) {
  HandleScope scope;

  int mode=args[0]->Int32Value();;

  glBlendEquation(mode);

  return Undefined();
}


JS_METHOD(BlendFunc) {
  HandleScope scope;

  int sfactor=args[0]->Int32Value();;
  int dfactor=args[1]->Int32Value();;

  glBlendFunc(sfactor,dfactor);

  return Undefined();
}


JS_METHOD(EnableVertexAttribArray) {
  HandleScope scope;

  glEnableVertexAttribArray(args[0]->Int32Value());

  return Undefined();
}


JS_METHOD(VertexAttribPointer) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  int size = args[1]->Int32Value();
  int type = args[2]->Int32Value();
  int normalized = args[3]->BooleanValue();
  int stride = args[4]->Int32Value();
  int offset = args[5]->Int32Value();

  //    printf("VertexAttribPointer %d %d %d %d %d %d\n", indx, size, type, normalized, stride, offset);
  glVertexAttribPointer(indx, size, type, normalized, stride, (const GLvoid *)offset);

  return Undefined();
}


JS_METHOD(ActiveTexture) {
  HandleScope scope;

  glActiveTexture(args[0]->Int32Value());
  return Undefined();
}


JS_METHOD(DrawElements) {
  HandleScope scope;

  int mode = args[0]->Int32Value();
  int count = args[1]->Int32Value();
  int type = args[2]->Int32Value();
  int offset = args[3]->Int32Value();
  glDrawElements(mode, count, type, (const GLvoid*)offset);
  return Undefined();
}


JS_METHOD(Flush) {
  HandleScope scope;
  glFlush();
  return Undefined();
}

JS_METHOD(Finish) {
  HandleScope scope;
  glFinish();
  return Undefined();
}

JS_METHOD(VertexAttrib1f) {
  HandleScope scope;

  GLuint indx = args[0]->Int32Value();
  GLfloat x = args[1]->NumberValue();

  glVertexAttrib1f(indx, x);
  return Undefined();
}

JS_METHOD(VertexAttrib2f) {
  HandleScope scope;

  GLuint indx = args[0]->Int32Value();
  GLfloat x = args[1]->NumberValue();
  GLfloat y = args[2]->NumberValue();

  glVertexAttrib2f(indx, x, y);
  return Undefined();
}

JS_METHOD(VertexAttrib3f) {
  HandleScope scope;

  GLuint indx = args[0]->Int32Value();
  GLfloat x = args[1]->NumberValue();
  GLfloat y = args[2]->NumberValue();
  GLfloat z = args[3]->NumberValue();

  glVertexAttrib3f(indx, x, y, z);
  return Undefined();
}

JS_METHOD(VertexAttrib4f) {
  HandleScope scope;

  GLuint indx = args[0]->Int32Value();
  GLfloat x = args[1]->NumberValue();
  GLfloat y = args[2]->NumberValue();
  GLfloat z = args[3]->NumberValue();
  GLfloat w = args[4]->NumberValue();

  glVertexAttrib4f(indx, x, y, z, w);
  return Undefined();
}

inline void *getArrayData(Local<Value> arg) {
  void *data=NULL;
  if(!arg->IsNull()) {
    if(arg->IsArray()) {
      Local<Array> arr = Array::Cast(*arg);
      data = arr->GetIndexedPropertiesExternalArrayData();
    }
    else if(arg->IsObject()) {
      data = arg->ToObject()->GetIndexedPropertiesExternalArrayData();
    }
    else
      ThrowException(JS_STR("Bad array argument"));
  }

  return data;
}


JS_METHOD(VertexAttrib1fv) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);

  void *data = getArrayData(args[1]);
  if(data) glVertexAttrib1fv(indx, (float*) data);

  return Undefined();
}

JS_METHOD(VertexAttrib2fv) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  void *data = getArrayData(args[1]);
  if(data) glVertexAttrib2fv(indx, (float*) data);

  return Undefined();
}

JS_METHOD(VertexAttrib3fv) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  void *data = getArrayData(args[1]);
  if(data) glVertexAttrib3fv(indx, (float*) data);

  return Undefined();
}

JS_METHOD(VertexAttrib4fv) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  void *data = getArrayData(args[1]);
  if(data) glVertexAttrib4fv(indx, (float*) data);

  return Undefined();
}

JS_METHOD(BlendColor) {
  HandleScope scope;

  GLclampf r= args[0]->Int32Value();
  GLclampf g= args[1]->Int32Value();
  GLclampf b= args[2]->Int32Value();
  GLclampf a= args[3]->Int32Value();

  glBlendColor(r,g,b,a);
  return Undefined();
}

JS_METHOD(BlendEquationSeparate) {
  HandleScope scope;

  GLenum modeRGB= args[0]->Int32Value();
  GLenum modeAlpha= args[1]->Int32Value();

  glBlendEquationSeparate(modeRGB,modeAlpha);
  return Undefined();
}

JS_METHOD(BlendFuncSeparate) {
  HandleScope scope;

  GLenum srcRGB= args[0]->Int32Value();
  GLenum dstRGB= args[1]->Int32Value();
  GLenum srcAlpha= args[2]->Int32Value();
  GLenum dstAlpha= args[3]->Int32Value();

  glBlendFuncSeparate(srcRGB,dstRGB,srcAlpha,dstAlpha);
  return Undefined();
}

JS_METHOD(ClearStencil) {
  HandleScope scope;

  GLint s = args[0]->Int32Value();

  glClearStencil(s);
  return Undefined();
}

JS_METHOD(ColorMask) {
  HandleScope scope;

  GLboolean r = args[0]->BooleanValue();
  GLboolean g = args[1]->BooleanValue();
  GLboolean b = args[2]->BooleanValue();
  GLboolean a = args[3]->BooleanValue();

  glColorMask(r,g,b,a);
  return Undefined();
}

JS_METHOD(CopyTexImage2D) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLint level = args[1]->Int32Value();
  GLenum internalformat = args[2]->Int32Value();
  GLint x = args[3]->Int32Value();
  GLint y = args[4]->Int32Value();
  GLsizei width = args[5]->Int32Value();
  GLsizei height = args[6]->Int32Value();
  GLint border = args[7]->Int32Value();

  glCopyTexImage2D( target, level, internalformat, x, y, width, height, border);
  return Undefined();
}

JS_METHOD(CopyTexSubImage2D) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLint level = args[1]->Int32Value();
  GLint xoffset = args[2]->Int32Value();
  GLint yoffset = args[3]->Int32Value();
  GLint x = args[4]->Int32Value();
  GLint y = args[5]->Int32Value();
  GLsizei width = args[6]->Int32Value();
  GLsizei height = args[7]->Int32Value();

  glCopyTexSubImage2D( target, level, xoffset, yoffset, x, y, width, height);
  return Undefined();
}

JS_METHOD(CullFace) {
  HandleScope scope;

  GLenum mode = args[0]->Int32Value();

  glCullFace(mode);
  return Undefined();
}

JS_METHOD(DepthMask) {
  HandleScope scope;

  GLboolean flag = args[0]->BooleanValue();

  glDepthMask(flag);
  return Undefined();
}

JS_METHOD(DepthRange) {
  HandleScope scope;

  GLclampf zNear = args[0]->Int32Value();
  GLclampf zFar = args[1]->Int32Value();

  glDepthRangef(zNear, zFar);
  return Undefined();
}

JS_METHOD(DisableVertexAttribArray) {
  HandleScope scope;

  GLuint index = args[0]->Int32Value();

  glDisableVertexAttribArray(index);
  return Undefined();
}

JS_METHOD(Hint) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLenum mode = args[1]->Int32Value();

  glHint(target, mode);
  return Undefined();
}

JS_METHOD(IsEnabled) {
  HandleScope scope;

  GLenum cap = args[0]->Int32Value();

  bool ret=glIsEnabled(cap);
  return scope.Close(Boolean::New(ret));
}

JS_METHOD(LineWidth) {
  HandleScope scope;

  GLfloat width = args[0]->NumberValue();

  glLineWidth(width);
  return Undefined();
}

JS_METHOD(PolygonOffset) {
  HandleScope scope;

  GLfloat factor = args[0]->NumberValue();
  GLfloat units = args[1]->NumberValue();

  glPolygonOffset(factor, units);
  return Undefined();
}

JS_METHOD(SampleCoverage) {
  HandleScope scope;

  GLclampf value = args[0]->Int32Value();
  GLboolean invert = args[1]->BooleanValue();

  glSampleCoverage(value, invert);
  return Undefined();
}

JS_METHOD(Scissor) {
  HandleScope scope;

  GLint x = args[0]->Int32Value();
  GLint y = args[1]->Int32Value();
  GLsizei width = args[2]->Int32Value();
  GLsizei height = args[3]->Int32Value();

  glScissor(x, y, width, height);
  return Undefined();
}

JS_METHOD(StencilFunc) {
  HandleScope scope;

  GLenum func = args[0]->Int32Value();
  GLint ref = args[1]->Int32Value();
  GLuint mask = args[2]->Int32Value();

  glStencilFunc(func, ref, mask);
  return Undefined();
}

JS_METHOD(StencilFuncSeparate) {
  HandleScope scope;

  GLenum face = args[0]->Int32Value();
  GLenum func = args[1]->Int32Value();
  GLint ref = args[2]->Int32Value();
  GLuint mask = args[3]->Int32Value();

  glStencilFuncSeparate(face, func, ref, mask);
  return Undefined();
}

JS_METHOD(StencilMask) {
  HandleScope scope;

  GLuint mask = args[0]->Uint32Value();

  glStencilMask(mask);
  return Undefined();
}

JS_METHOD(StencilMaskSeparate) {
  HandleScope scope;

  GLenum face = args[0]->Int32Value();
  GLuint mask = args[1]->Uint32Value();

  glStencilMaskSeparate(face, mask);
  return Undefined();
}

JS_METHOD(StencilOp) {
  HandleScope scope;

  GLenum fail = args[0]->Int32Value();
  GLenum zfail = args[1]->Int32Value();
  GLenum zpass = args[2]->Int32Value();

  glStencilOp(fail, zfail, zpass);
  return Undefined();
}

JS_METHOD(StencilOpSeparate) {
  HandleScope scope;

  GLenum face = args[0]->Int32Value();
  GLenum fail = args[1]->Int32Value();
  GLenum zfail = args[2]->Int32Value();
  GLenum zpass = args[3]->Int32Value();

  glStencilOpSeparate(face, fail, zfail, zpass);
  return Undefined();
}

JS_METHOD(BindRenderbuffer) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLuint buffer = args[1]->Int32Value();

  glBindRenderbuffer(target, buffer);

  return Undefined();
}

JS_METHOD(CreateRenderbuffer) {
  HandleScope scope;

  GLuint renderbuffers;
  glGenRenderbuffers(1,&renderbuffers);
  return scope.Close(Number::New(renderbuffers));
}

JS_METHOD(DeleteBuffer) {
  HandleScope scope;

  GLuint buffer = args[0]->Uint32Value();

  glDeleteBuffers(1,&buffer);
  return Undefined();
}

JS_METHOD(DeleteFramebuffer) {
  HandleScope scope;

  GLuint buffer = args[0]->Uint32Value();

  glDeleteFramebuffers(1,&buffer);
  return Undefined();
}

JS_METHOD(DeleteProgram) {
  HandleScope scope;

  GLuint program = args[0]->Uint32Value();

  glDeleteProgram(program);
  return Undefined();
}

JS_METHOD(DeleteRenderbuffer) {
  HandleScope scope;

  GLuint renderbuffer = args[0]->Uint32Value();

  glDeleteRenderbuffers(1, &renderbuffer);
  return Undefined();
}

JS_METHOD(DeleteShader) {
  HandleScope scope;

  GLuint shader = args[0]->Uint32Value();

  glDeleteShader(shader);
  return Undefined();
}

JS_METHOD(DeleteTexture) {
  HandleScope scope;

  GLuint texture = args[0]->Uint32Value();

  glDeleteTextures(1,&texture);
  return Undefined();
}

JS_METHOD(DetachShader) {
  HandleScope scope;

  GLuint program = args[0]->Uint32Value();
  GLuint shader = args[1]->Uint32Value();

  glDetachShader(program, shader);
  return Undefined();
}

JS_METHOD(FramebufferRenderbuffer) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLenum attachment = args[1]->Int32Value();
  GLenum renderbuffertarget = args[2]->Int32Value();
  GLuint renderbuffer = args[3]->Uint32Value();

  glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
  return Undefined();
}

JS_METHOD(GetVertexAttribOffset) {
  HandleScope scope;

  GLuint index = args[0]->Uint32Value();
  GLenum pname = args[1]->Int32Value();
  void *ret=NULL;

  glGetVertexAttribPointerv(index, pname, &ret);
  return scope.Close(Integer::New((GLsizeiptr) ret)); // TODO is this correct?
}

JS_METHOD(IsBuffer) {
  HandleScope scope;

  return scope.Close(Boolean::New(glIsBuffer(args[0]->Uint32Value())));
}

JS_METHOD(IsFramebuffer) {
  HandleScope scope;

  return scope.Close(Boolean::New(glIsFramebuffer(args[0]->Uint32Value())));
}

JS_METHOD(IsProgram) {
  HandleScope scope;

  return scope.Close(Boolean::New(glIsProgram(args[0]->Uint32Value())));
}

JS_METHOD(IsRenderbuffer) {
  HandleScope scope;

  return scope.Close(Boolean::New(glIsRenderbuffer( args[0]->Uint32Value())));
}

JS_METHOD(IsShader) {
  HandleScope scope;

  return scope.Close(Boolean::New(glIsShader(args[0]->Uint32Value())));
}

JS_METHOD(IsTexture) {
  HandleScope scope;

  return scope.Close(Boolean::New(glIsTexture(args[0]->Uint32Value())));
}

JS_METHOD(RenderbufferStorage) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLenum internalformat = args[1]->Int32Value();
  GLsizei width = args[2]->Uint32Value();
  GLsizei height = args[3]->Uint32Value();

  glRenderbufferStorage(target, internalformat, width, height);
  return Undefined();
}

JS_METHOD(GetShaderSource) {
  HandleScope scope;

  int shader = args[0]->Int32Value();

  GLint len;
  glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &len);
  GLchar *source=new GLchar[len];
  glGetShaderSource(shader, len, NULL, source);

  Local<String> str=String::New(source);
  delete source;

  return str;
}

JS_METHOD(ValidateProgram) {
  HandleScope scope;

  glValidateProgram(args[0]->Int32Value());

  return Undefined();
}

JS_METHOD(TexSubImage2D) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLint level = args[1]->Int32Value();
  GLint xoffset = args[2]->Int32Value();
  GLint yoffset = args[3]->Int32Value();
  GLsizei width = args[4]->Int32Value();
  GLsizei height = args[5]->Int32Value();
  GLenum format = args[6]->Int32Value();
  GLenum type = args[7]->Int32Value();
  void *pixels=getImageData(args[8]);

  if(pixels)
    glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);

  return Undefined();
}

JS_METHOD(ReadPixels) {
  HandleScope scope;

  GLint x = args[0]->Int32Value();
  GLint y = args[1]->Int32Value();
  GLsizei width = args[2]->Int32Value();
  GLsizei height = args[3]->Int32Value();
  GLenum format = args[4]->Int32Value();
  GLenum type = args[5]->Int32Value();
  void *pixels=getImageData(args[6]);

  if(pixels)
    glReadPixels(x, y, width, height, format, type, pixels);

  return Undefined();
}

JS_METHOD(GetTexParameter) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLenum pname = args[1]->Int32Value();

  GLint param_value=0;
  glGetTexParameteriv(target, pname, &param_value);

  return scope.Close(Number::New(param_value));
}

JS_METHOD(GetActiveAttrib) {
  HandleScope scope;

  GLuint program = args[0]->Int32Value();
  GLuint index = args[1]->Int32Value();

  char name[1024];
  GLsizei length=0;
  GLenum type;
  GLsizei size;
  glGetActiveAttrib(program, index, 1024, &length, &size, &type, name);

  Local<Array> activeInfo = Array::New(3);
  activeInfo->Set(JS_STR("size"), JS_INT(size));
  activeInfo->Set(JS_STR("type"), JS_INT(type));
  activeInfo->Set(JS_STR("name"), JS_STR(name));

  return scope.Close(activeInfo);
}

JS_METHOD(GetActiveUniform) {
  HandleScope scope;

  GLuint program = args[0]->Int32Value();
  GLuint index = args[1]->Int32Value();

  char name[1024];
  GLsizei length=0;
  GLenum type;
  GLsizei size;
  glGetActiveUniform(program, index, 1024, &length, &size, &type, name);

  Local<Array> activeInfo = Array::New(3);
  activeInfo->Set(JS_STR("size"), JS_INT(size));
  activeInfo->Set(JS_STR("type"), JS_INT(type));
  activeInfo->Set(JS_STR("name"), JS_STR(name));

  return scope.Close(activeInfo);
}

JS_METHOD(GetAttachedShaders) {
  HandleScope scope;

  GLuint program = args[0]->Int32Value();

  GLuint shaders[1024];
  GLsizei count;
  glGetAttachedShaders(program, 1024, &count, shaders);

  Local<Array> shadersArr = Array::New(count);
  for(int i=0;i<count;i++)
    shadersArr->Set(i, JS_INT(shaders[i]));

  return scope.Close(shadersArr);
}

JS_METHOD(GetParameter) {
  HandleScope scope;

  GLenum name = args[0]->Int32Value();

  switch(name) {
  case GL_BLEND:
  case GL_CULL_FACE:
  case GL_DEPTH_TEST:
  case GL_DEPTH_WRITEMASK:
  case GL_DITHER:
  case GL_POLYGON_OFFSET_FILL:
  case GL_SAMPLE_COVERAGE_INVERT:
  case GL_SCISSOR_TEST:
  case GL_STENCIL_TEST:
  case 0x9240 /* UNPACK_FLIP_Y_WEBGL */:
  case 0x9241 /* UNPACK_PREMULTIPLY_ALPHA_WEBGL*/:
  {
    // return a boolean
    GLboolean params;
    ::glGetBooleanv(name, &params);
    return scope.Close(JS_BOOL(params));
  }
  case GL_DEPTH_CLEAR_VALUE:
  case GL_LINE_WIDTH:
  case GL_POLYGON_OFFSET_FACTOR:
  case GL_POLYGON_OFFSET_UNITS:
  case GL_SAMPLE_COVERAGE_VALUE:
  {
    // return a float
    GLfloat params;
    ::glGetFloatv(name, &params);
    return scope.Close(JS_FLOAT(params));
  }
  case GL_RENDERER:
  case GL_SHADING_LANGUAGE_VERSION:
  case GL_VENDOR:
  case GL_VERSION:
  {
    // return a string
    char *params=(char*) ::glGetString(name);
    return scope.Close(JS_STR(params));
  }
  case GL_MAX_VIEWPORT_DIMS:
  {
    // return a int32[2]
    GLint params[2];
    ::glGetIntegerv(name, params);
    node::Buffer *buf=node::Buffer::New(2*sizeof(int));
    ((int*)Buffer::Data(buf))[0]=params[0];
    ((int*)Buffer::Data(buf))[1]=params[1];
    return scope.Close(buf->handle_);
  }
  case GL_SCISSOR_BOX:
  case GL_VIEWPORT:
  {
    // return a int32[4]
    GLint params[4];
    ::glGetIntegerv(name, params);
    node::Buffer *buf=node::Buffer::New(4*sizeof(int));
    ((int*)Buffer::Data(buf))[0]=params[0];
    ((int*)Buffer::Data(buf))[1]=params[1];
    ((int*)Buffer::Data(buf))[2]=params[2];
    ((int*)Buffer::Data(buf))[3]=params[3];
    return scope.Close(buf->handle_);
  }
  case GL_ALIASED_LINE_WIDTH_RANGE:
  case GL_ALIASED_POINT_SIZE_RANGE:
  case GL_DEPTH_RANGE:
  {
    // return a float[2]
    GLfloat params[2];
    ::glGetFloatv(name, params);
    node::Buffer *buf=node::Buffer::New(2*sizeof(float));
    ((float*)Buffer::Data(buf))[0]=params[0];
    ((float*)Buffer::Data(buf))[1]=params[1];
    return scope.Close(buf->handle_);
  }
  case GL_BLEND_COLOR:
  case GL_COLOR_CLEAR_VALUE:
  {
    // return a float[4]
    GLfloat params[4];
    ::glGetFloatv(name, params);
    node::Buffer *buf=node::Buffer::New(4*sizeof(float));
    ((float*)Buffer::Data(buf))[0]=params[0];
    ((float*)Buffer::Data(buf))[1]=params[1];
    ((float*)Buffer::Data(buf))[2]=params[2];
    ((float*)Buffer::Data(buf))[3]=params[3];
    return scope.Close(buf->handle_);
  }
  case GL_COLOR_WRITEMASK:
  {
    // return a boolean[4]
    GLboolean params[4];
    ::glGetBooleanv(name, params);
    Local<Array> arr=Array::New(4);
    arr->Set(0,JS_BOOL(params[0]));
    arr->Set(1,JS_BOOL(params[1]));
    arr->Set(2,JS_BOOL(params[2]));
    arr->Set(3,JS_BOOL(params[3]));
    return scope.Close(arr);
  }
  case GL_ARRAY_BUFFER_BINDING:
  case GL_CURRENT_PROGRAM:
  case GL_ELEMENT_ARRAY_BUFFER_BINDING:
  case GL_FRAMEBUFFER_BINDING:
  case GL_RENDERBUFFER_BINDING:
  case GL_TEXTURE_BINDING_2D:
  case GL_TEXTURE_BINDING_CUBE_MAP:
  {
    GLint params;
    ::glGetIntegerv(name, &params);
    return scope.Close(JS_INT(params));
  }
  default: {
    // return a long
    GLint params;
    ::glGetIntegerv(name, &params);
    return scope.Close(JS_INT(params));
  }
  }

  return Undefined();
}

JS_METHOD(GetBufferParameter) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLenum pname = args[1]->Int32Value();

  GLint params;
  glGetBufferParameteriv(target,pname,&params);
  return scope.Close(JS_INT(params));
}

JS_METHOD(GetFramebufferAttachmentParameter) {
  HandleScope scope;

  GLenum target = args[0]->Int32Value();
  GLenum attachment = args[1]->Int32Value();
  GLenum pname = args[2]->Int32Value();

  GLint params;
  glGetFramebufferAttachmentParameteriv(target,attachment, pname,&params);
  return scope.Close(JS_INT(params));
}

JS_METHOD(GetProgramInfoLog) {
  HandleScope scope;

  GLuint program = args[0]->Int32Value();
  int Len = 1024;
  char Error[1024];
  glGetProgramInfoLog(program, 1024, &Len, Error);

  return scope.Close(String::New(Error));
}

JS_METHOD(GetRenderbufferParameter) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  int value = 0;
  glGetRenderbufferParameteriv(target,pname,&value);

  return scope.Close(JS_INT(value));
}

// TODO GetUniform() not sure how to retrieve type of uniform at location in program
JS_METHOD(GetUniform) {
  HandleScope scope;

  /*GLuint program = args[0]->Int32Value();
  GLuint location = args[1]->Int32Value();
  float *data=new float[16]; // worst case scenario is 16 floats

  glGetUniformfv(program, location, data);*/

  return Undefined();
}

JS_METHOD(GetVertexAttrib) {
  HandleScope scope;

  GLuint index = args[0]->Int32Value();
  GLuint pname = args[1]->Int32Value();

  GLint value=0;

  switch (pname) {
  case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
  case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:
    glGetVertexAttribiv(index,pname,&value);
    return scope.Close(JS_BOOL(value));
  case GL_VERTEX_ATTRIB_ARRAY_SIZE:
  case GL_VERTEX_ATTRIB_ARRAY_STRIDE:
  case GL_VERTEX_ATTRIB_ARRAY_TYPE:
    glGetVertexAttribiv(index,pname,&value);
    return scope.Close(JS_INT(value));
  case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
    glGetVertexAttribiv(index,pname,&value);
    return scope.Close(JS_INT(value));
  case GL_CURRENT_VERTEX_ATTRIB:
    float vextex_attribs[4];
    glGetVertexAttribfv(index,pname,vextex_attribs);
    return scope.Close(node::Buffer::New((char*)vextex_attribs, 4*4)->handle_);
  default:
    return ThrowError("GetVertexAttrib: Invalid Enum");
  }

}

JS_METHOD(GetSupportedExtensions) {
  HandleScope scope;

  char *extensions=(char*) glGetString(GL_EXTENSIONS);

  return scope.Close(JS_STR(extensions));
}

// TODO GetExtension(name) return the extension name if found, should be an object...
JS_METHOD(GetExtension) {
  HandleScope scope;

  String::AsciiValue name(args[0]);
  char *sname=*name;
  char *extensions=(char*) glGetString(GL_EXTENSIONS);

  char *ext=strcasestr(extensions, sname);

  if(!ext) return Undefined();
  return scope.Close(JS_STR(ext, ::strlen(sname)));
}

JS_METHOD(CheckFramebufferStatus) {
  HandleScope scope;

  GLenum target=args[0]->Int32Value();

  return scope.Close(JS_INT(glCheckFramebufferStatus(target)));
}

} // end namespace webgl

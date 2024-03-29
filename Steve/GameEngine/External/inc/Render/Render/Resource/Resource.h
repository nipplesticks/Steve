#pragma once

#include <Common/DMath.h>
#include <Common/Typedef.h>
#include <d3d12.h>
#include <string>

namespace Render
{
  class Resource
  {
  public:
    union Resource_View
    {
      D3D12_VERTEX_BUFFER_VIEW        vbv;
      D3D12_INDEX_BUFFER_VIEW         ibv;
      D3D12_STREAM_OUTPUT_BUFFER_VIEW sobv;
    };
    enum class Resource_Type
    {
      Unknown = 0,
      ConstantBuffer,
      Texture1D,
      Texture2D,
      Texture3D,
      StructuredBuffer,
      VertexBuffer,
      IndexBuffer,
      RenderTarget,
      DepthBuffer,
      NrOfSupportedTypes
    };

  public:
    Resource()          = default;
    virtual ~Resource() = default;

    static D3D12_UAV_DIMENSION GetUAVDimension(Resource* resource_p);
    static D3D12_SRV_DIMENSION GetSRVDimension(Resource* resource_p);

    void Init(Resource_Type      resourceType,
              const std::string& name,
              uint32             width,
              DXGI_FORMAT        format       = DXGI_FORMAT_UNKNOWN,
              uint32             height       = 1u,
              uint32             depth        = 1u,
              uint32             nrOfElements = 1u);

    void Init(const std::string&     name,
              D3D12_HEAP_PROPERTIES* heapProperties,
              D3D12_RESOURCE_DESC*   resourceDesc,
              D3D12_HEAP_FLAGS       heapFlags,
              D3D12_RESOURCE_STATES  initialState,
              D3D12_CLEAR_VALUE*     clearValue = nullptr);

    void Update(void*                 data_p,
                D3D12_RESOURCE_STATES stateAfter = D3D12_RESOURCE_STATE_GENERIC_READ,
                uint64                sizeofData = 0,
                uint64                offset     = 0);

    uint64 GetRowPitch();

    const DM::Vec3u& GetDimention() const;

    void SetState(D3D12_RESOURCE_STATES state);

    ID3D12Resource*       GetResource() const;
    D3D12_RESOURCE_STATES GetState() const;
    const Resource_View&  GetView() const;
    DXGI_FORMAT           GetFormat() const;
    uint64                GetBufferSize() const;
    uint32                GetElementSize() const;
    uint32                GetElementCount() const;
    uint32                GetNumberOfRows() const;
    Resource_Type         GetResourceType() const;
    virtual uint32        GetClassSize() const;

  protected:
    D3D12_RESOURCE_DIMENSION _GetResourceDimension(Resource_Type resourceType);

    ID3D12Resource*       myResource_p   = nullptr;
    DXGI_FORMAT           myFormat       = DXGI_FORMAT_UNKNOWN;
    D3D12_RESOURCE_STATES myState        = {};
    uint64                myBufferSize   = 0u;
    uint32                myElementSize  = 0u;
    DM::Vec3u             myDimention    = DM::Vec3u(0, 0, 0);
    Resource_Type         myResourceType = Resource_Type::Unknown;
    Resource_View         myResourceView;
    uint64                myRowPitch         = 0;
    uint32                myNumberOfElements = 0;
    uint32                myNumberOfRows     = 0;
  };
} // namespace Render
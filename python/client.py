# python/client.py
import grpc
import time
import data_pb2
import data_pb2_grpc

def generate_data(id):
    return data_pb2.DataMessage(
        id=id,
        payload=b"Sample payload",  # Simulate binary data (e.g., image/file)
        timestamp=str(time.time())
    )

def run():
    channel = grpc.insecure_channel('localhost:50051')
    stub = data_pb2_grpc.DataServiceStub(channel)
    
    # Send 3 data points
    for i in range(1, 4):
        data = generate_data(i)
        stub.PushData(data)
        print(f"Sent data ID: {i}")

if __name__ == '__main__':
    run()
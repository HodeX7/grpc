# python/client.py
import grpc
import time
import json
import data_pb2
import data_pb2_grpc

def load_config():
    with open('config.json', 'r') as f:
        return json.load(f)

def send_data(stub, id):
    try:
        data = data_pb2.DataMessage(
            id=id,
            payload=b"SampleData",
            timestamp=str(time.time())
        )
        stub.PushData(data)
        print(f"Sent data ID: {id}")
    except grpc.RpcError as e:
        print(f"Failed to send data ID {id}: {e}")

def run():
    # Load configuration
    config = load_config()
    target = config['target']
    server_address = f"{target['ip']}:{target['port']}"
    
    print(f"Connecting to server at {server_address}")
    channel = grpc.insecure_channel(server_address)
    stub = data_pb2_grpc.DataServiceStub(channel)
    
    # Send 5 data points
    for i in range(1, 11):
        send_data(stub, i)
        time.sleep(1)  # Add delay between sends
        
    # Send duplicate IDs
    for _ in range(5):
        send_data(stub, 5)  # Sending duplicate ID 50

if __name__ == '__main__':
    run()
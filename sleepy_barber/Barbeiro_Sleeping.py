from threading import Thread, Lock, Event
import time
import random
 
mutex = Lock()
 
class BarberShop:
    waitingCustomers = []
 
    def __init__(self, barber, number_of_seats):
        self.barber = barber
        self.numberOfSeats = number_of_seats
 
    def open_shop(self):
        print('Barbearia aberta!')
        working_thread = Thread(target=self.barber_go_to_work) 
        working_thread.start()
 
    def barber_go_to_work(self):
        while True:
            mutex.acquire() 
            if(len(self.waitingCustomers) > 0):
                c = self.waitingCustomers[0]
                del self.waitingCustomers[0]
                mutex.release()
                self.barber.cut_hair(c)
            else:
                mutex.release()
                print('O barbeiro está dormindo! (Esperando)')
                barber.sleep()
                print('O barbeiro acordou! (Pronto)')
 
  
    def enter_barber_shop(self, customer):
        mutex.acquire()
        print('-------------------------------------------------------')
        print(f'[ENTRADA] - {customer.name} entra na barbearia!')
 

        if len(self.waitingCustomers) == self.numberOfSeats:
            print(f'[SAÍDA] - Não há cadeiras restantes na barbearia, {customer.name} está indo embora!')
            mutex.release()
        else:
            print(f'[ESPERANDO] - {customer.name} sentou na cadeira de espera!')
            self.waitingCustomers.append(c) 
            mutex.release() 
            barber.wake_up()
 
 
class Customer:
    def __init__(self, name):
        self.name = name
 
class Barber:
    barberWorkingEvent = Event()
 
    def sleep(self):
        self.barberWorkingEvent.wait()
 
    def wake_up(self):
        self.barberWorkingEvent.set()
 
    def cut_hair(self, customer):
        self.barberWorkingEvent.clear()
        print(f'[TRABALHANDO] - {customer.name} está cortando o cabelo!')
        time.sleep(4)
        print(f'[FINALIZADO] - {customer.name} finalizou o corte!')

if __name__ == '__main__':
 
    customers = list([])
    
    for x in range(50):
      customers.append(Customer(x))
    
    barber = Barber()
    barberShop = BarberShop(barber, 3)
    barberShop.open_shop()
 
    while len(customers) > 0:
        c = customers.pop()
        barberShop.enter_barber_shop(c)
        time.sleep(4)
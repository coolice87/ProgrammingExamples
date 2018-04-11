package ws

import (
	"github.com/garyburd/redigo/redis"
	"fmt"
	"time"
)

type redisClient struct {
	pool *redis.Pool
}

var (
	cacheKey = "onlineClient"
)

func (c *redisClient) GetAll() {
	conn := c.pool.Get()
	clients,err := redis.StringMap(conn.Do("HGETALL", cacheKey))
	if err != nil {
		panic(err)
	}

	fmt.Printf("online client: %d \n", len(clients))
	for uId,client := range clients {
		fmt.Printf("%s -- %s\n", uId, client)
	}
}

func (c *redisClient) GetOne(id string) {
	client,err := redis.String(c.pool.Get().Do("HGET", cacheKey, id))
	if err != nil {
		panic(err)
	}
	fmt.Println(client)
}

func (c *redisClient) Kick(id string) {
	result,err := c.pool.Get().Do("HDEL", cacheKey, id)
	if err != nil {
		panic(err)
	}
	fmt.Println(result)
}

func (c *redisClient) ClearAll() {
	result,err := c.pool.Get().Do("DEL", cacheKey)
	if err != nil {
		panic(err)
	}
	fmt.Println(result)
}

func (c *redisClient) Close() {
	if c.pool != nil {
		c.pool.Close()
	}
}

func NewClient(server, passwd string) *redisClient {
	return &redisClient{
			pool: NewPool(server, passwd),
		}
}

func (c *redisClient) Run (command string, args...interface{}) interface{} {
	result,err := c.pool.Get().Do(command, args...)
	if err != nil {
		fmt.Print(err)
		panic(err)
	}
	return result
}

func NewPool(server, passwd string) *redis.Pool {
	return &redis.Pool{
			MaxIdle: 3,
			IdleTimeout: 240* time.Second,
			Dial: func()(redis.Conn, error) {
				c,err := redis.Dial("tcp", server)
				if err != nil {
					return nil, err
				}

				if passwd != "" {
					if _,err := c.Do("AUTH", passwd); err != nil {
						c.Close()
						return nil,err
					}
				}
				return c,nil
			},
			TestOnBorrow: func(c redis.Conn, t time.Time) error {
				_,err := c.Do("PING")
				return err
			},
		}
}


